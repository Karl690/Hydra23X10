////////////////////////////////////////////////////////////////////////////////
// TinyUSB CDC HAL — same strategy as Robo_Grok_Core.
// RX bytes go into Hydra ReceiveCharacter() so serialProcessor is unchanged.
////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Serial.h"
#include "usb_otg_cdc.h"
#include "tusb.h"
#include "pinout.h"

uint32_t UsbCdcConfigured;
static uint32_t usb_was_mounted;

void OTG_FS_IRQHandler(void)
{
	tud_int_handler(0);
}

static void usb_clock_pins(void)
{
	pinInit(OTG_FS_DM);
	pinInit(OTG_FS_DP);
	RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
	(void)RCC->AHB2ENR;
}

void InitUsbCdc(void)
{
	UsbCdcConfigured = 0;
	usb_was_mounted = 0;
	usb_clock_pins();
	NVIC_SetPriority(OTG_FS_IRQn, 5u);
	NVIC_EnableIRQ(OTG_FS_IRQn);
	tud_init(BOARD_TUD_RHPORT);
}

void UsbCdc_Service(void)
{
	uint8_t buf[64];
	uint32_t n;
	uint32_t i;

	tud_task_ext(0, false);
	UsbCdcConfigured = tud_mounted() ? 1u : 0u;
	usb_was_mounted = UsbCdcConfigured; /* USB does not steal master; UART6 is default */

	n = tud_cdc_available();
	if (n > sizeof(buf)) n = sizeof(buf);
	if (n != 0u)
	{
		n = tud_cdc_read(buf, n);
		for (i = 0; i < n; i++)
		{
			if ((buf[i] == PING_CHAR) || (buf[i] == ABORT_CHAR))
				changeMasterCommPort(USB_MASTER);
			if (masterCommPort == USB_MASTER)
				ReceiveCharacter((char)buf[i]);
		}
	}
}
