#pragma once

#define RevisionHeader "HYDRA23X10"
#define MajorStep "4.256k"
#define RevisionDate "4/4/2026"
#define InstallPath "c:/repetrel/bin/firmware/"
#define SOFTWARE_MAJOR_REVISION     4   // XXX  update when a major change occurs (ie, protocol)
#define SOFTWARE_MINOR_REVISION     256 // XXX  update for major and minor changes
#define SOFTWARE_TWEAK_REVISION    'K'  // XXX  update for small changes ('z' is for experimental ONLY)
#define SOFTWARE_DEBUG_REVISION    'a'  // XXX  char update for debug versions  (applies to 'z' versions only  is for experimental ONLY) (display with M115)


// How to initialize string in C?
#define HB_STRING  "HB_4.256k"
//#define CONNECTIONSTRING ">GE:MEG Rev " MajorStep ":" RevisionDate ":STM32F407:---:"   //"1.000:0:0:0:USB"
/*added ability to define ABC as XYZ so you can use those connectors in case or blown pin
 *
 **/