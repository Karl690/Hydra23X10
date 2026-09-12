#ifndef usb_otg_cdc_HEADER
#define usb_otg_cdc_HEADER

#include <stdint.h>

extern uint32_t UsbCdcConfigured;

void InitUsbCdc(void);
void UsbCdc_Service(void);

#endif
