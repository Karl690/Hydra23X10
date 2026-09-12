# Rename VID_0483&PID_A407 COM ports to "ROBOT Com (COMx)".
# Does not use Set-PnpDeviceProperty (missing on some Windows builds).
# Run as Administrator via install_name.bat.

$ErrorActionPreference = 'Continue'

$priv = @'
using System;
using System.Runtime.InteropServices;
public class AdjPriv {
  [DllImport("advapi32.dll", ExactSpelling = true, SetLastError = true)]
  internal static extern bool AdjustTokenPrivileges(IntPtr htok, bool disall,
    ref TokPriv1Luid newst, int len, IntPtr prev, IntPtr relen);
  [DllImport("advapi32.dll", ExactSpelling = true, SetLastError = true)]
  internal static extern bool OpenProcessToken(IntPtr h, int acc, ref IntPtr phtok);
  [DllImport("advapi32.dll", SetLastError = true)]
  internal static extern bool LookupPrivilegeValue(string host, string name, ref long pluid);
  [StructLayout(LayoutKind.Sequential, Pack = 1)]
  internal struct TokPriv1Luid {
    public int Count;
    public long Luid;
    public int Attr;
  }
  public static bool Enable(string privilege) {
    IntPtr htok = IntPtr.Zero;
    if (!OpenProcessToken(System.Diagnostics.Process.GetCurrentProcess().Handle, 0x28, ref htok))
      return false;
    TokPriv1Luid tp;
    tp.Count = 1;
    tp.Luid = 0;
    tp.Attr = 2;
    if (!LookupPrivilegeValue(null, privilege, ref tp.Luid))
      return false;
    return AdjustTokenPrivileges(htok, false, ref tp, 0, IntPtr.Zero, IntPtr.Zero);
  }
}
'@
try { Add-Type $priv } catch { }

[void][AdjPriv]::Enable('SeTakeOwnershipPrivilege')
[void][AdjPriv]::Enable('SeRestorePrivilege')
[void][AdjPriv]::Enable('SeBackupPrivilege')

function Grant-KeyWrite([string]$rel) {
	$admin = New-Object System.Security.Principal.NTAccount('Administrators')
	$rk = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey(
		$rel,
		[Microsoft.Win32.RegistryKeyPermissionCheck]::ReadWriteSubTree,
		[System.Security.AccessControl.RegistryRights]::TakeOwnership)
	if ($rk -eq $null) { return $false }
	$acl = $rk.GetAccessControl([System.Security.AccessControl.AccessControlSections]::None)
	$acl.SetOwner($admin)
	$rk.SetAccessControl($acl)
	$rk.Close()

	$rk = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey(
		$rel,
		[Microsoft.Win32.RegistryKeyPermissionCheck]::ReadWriteSubTree,
		[System.Security.AccessControl.RegistryRights]::ChangePermissions)
	if ($rk -eq $null) { return $false }
	$acl = $rk.GetAccessControl()
	$rule = New-Object System.Security.AccessControl.RegistryAccessRule(
		$admin,
		[System.Security.AccessControl.RegistryRights]::FullControl,
		[System.Security.AccessControl.InheritanceFlags]::ContainerInherit,
		[System.Security.AccessControl.PropagationFlags]::None,
		[System.Security.AccessControl.AccessControlType]::Allow)
	$acl.AddAccessRule($rule)
	$rk.SetAccessControl($acl)
	$rk.Close()
	return $true
}

$usb = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey('SYSTEM\CurrentControlSet\Enum\USB')
if ($usb -eq $null) {
	Write-Host 'Cannot open Enum\USB'
	exit 1
}

$found = 0
foreach ($vid in $usb.GetSubKeyNames()) {
	$label = $null
	if ($vid -like 'VID_0483&PID_A407*') { $label = 'Robot407 Com' }
	elseif ($vid -like 'VID_0483&PID_A743*') { $label = 'Robot743 Com' }
	else { continue }
	$vidKey = $usb.OpenSubKey($vid)
	if ($vidKey -eq $null) { continue }
	foreach ($inst in $vidKey.GetSubKeyNames()) {
		$instKey = $vidKey.OpenSubKey($inst)
		if ($instKey -eq $null) { continue }
		$dp = $instKey.OpenSubKey('Device Parameters')
		$port = $null
		if ($dp -ne $null) { $port = $dp.GetValue('PortName') }
		if (-not $port) { continue }

		$name = "$label ($port)"
		$rel = "SYSTEM\CurrentControlSet\Enum\USB\$vid\$inst"
		Write-Host "Found $rel"
		Write-Host "  Port $port"

		if (-not (Grant-KeyWrite $rel)) {
			Write-Host '  Could not take ownership of the registry key.'
			continue
		}

		$w = [Microsoft.Win32.Registry]::LocalMachine.OpenSubKey(
			$rel,
			[Microsoft.Win32.RegistryKeyPermissionCheck]::ReadWriteSubTree,
			[System.Security.AccessControl.RegistryRights]::SetValue)
		if ($w -eq $null) {
			Write-Host '  Open for write failed.'
			continue
		}
		$w.SetValue('FriendlyName', $name, [Microsoft.Win32.RegistryValueKind]::String)
		$w.SetValue('DeviceDesc', $name, [Microsoft.Win32.RegistryValueKind]::String)
		$w.Close()
		Write-Host "  Set name to $name"
		$found++
	}
}

if ($found -eq 0) {
	Write-Host 'No matching COM port. Plug the board in so it shows as USB Serial Device (COMx), then run this again.'
	exit 1
}

Write-Host "Renamed $found port(s). Switch away from Device Manager and back, or unplug/replug."
exit 0
