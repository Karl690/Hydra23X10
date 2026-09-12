////////////////////////////////////////////////////////////////////////////////
//
// File:    usb_descriptors.c
//
////////////////////////////////////////////////////////////////////////////////
//
// Purpose: TinyUSB CDC-ACM descriptors for Com[0]. IAD CDC so Windows 10+
//          binds usbser without a custom INF. PID is not ST 0x5740 so the
//          ST "Virtual COM Port" driver does not override the product name.
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include "tusb.h"
#include "device/usbd.h"

#define USB_VID   0x0483
#if defined(STM32H743xx)
#define USB_PID            0xA743
#define USB_PRODUCT_NAME   "Robot743 Com"
#define USB_SERIAL_NAME    "H743"
#else
#define USB_PID            0xA407
#define USB_PRODUCT_NAME   "Robot407 Com"
#define USB_SERIAL_NAME    "F407"
#endif
#define USB_BCD   0x0210          /* 2.1 so Windows asks for BOS / MS OS 2.0 */
#define USB_VENDOR_CODE  1

tusb_desc_device_t const desc_device = {
	.bLength            = sizeof(tusb_desc_device_t),
	.bDescriptorType    = TUSB_DESC_DEVICE,
	.bcdUSB             = USB_BCD,
	.bDeviceClass       = TUSB_CLASS_MISC,
	.bDeviceSubClass    = MISC_SUBCLASS_COMMON,
	.bDeviceProtocol    = MISC_PROTOCOL_IAD,
	.bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
	.idVendor           = USB_VID,
	.idProduct          = USB_PID,
	.bcdDevice          = 0x0102,
	.iManufacturer      = 0x01,
	.iProduct           = 0x02,
	.iSerialNumber      = 0x03,
	.bNumConfigurations = 0x01
};

uint8_t const *tud_descriptor_device_cb(void)
{
	return (uint8_t const *)&desc_device;
}

enum {
	ITF_NUM_CDC = 0,
	ITF_NUM_CDC_DATA,
	ITF_NUM_TOTAL
};

#define EPNUM_CDC_NOTIF  0x81
#define EPNUM_CDC_OUT    0x02
#define EPNUM_CDC_IN     0x82

#define CONFIG_TOTAL_LEN  (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN)

uint8_t const desc_fs_configuration[] = {
	TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x80, 100),
	TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64)
};

uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
	(void)index;
	return desc_fs_configuration;
}

#define MS_OS_20_DESC_LEN  146
#define BOS_TOTAL_LEN      (TUD_BOS_DESC_LEN + TUD_BOS_MICROSOFT_OS_DESC_LEN)

uint8_t const desc_bos[] = {
	TUD_BOS_DESCRIPTOR(BOS_TOTAL_LEN, 1),
	TUD_BOS_MS_OS_20_DESCRIPTOR(MS_OS_20_DESC_LEN, USB_VENDOR_CODE)
};

uint8_t const *tud_descriptor_bos_cb(void)
{
	return desc_bos;
}

uint8_t const desc_ms_os_20[] = {
	/* Set header: Win 8.1+, total length */
	U16_TO_U8S_LE(0x000A), U16_TO_U8S_LE(MS_OS_20_SET_HEADER_DESCRIPTOR),
	U32_TO_U8S_LE(0x06030000), U16_TO_U8S_LE(MS_OS_20_DESC_LEN),

	/* Configuration subset, bConfigurationValue = 1 */
	U16_TO_U8S_LE(0x0008), U16_TO_U8S_LE(MS_OS_20_SUBSET_HEADER_CONFIGURATION),
	1, 0, U16_TO_U8S_LE(MS_OS_20_DESC_LEN - 10),

	/* Function subset, first interface = CDC */
	U16_TO_U8S_LE(0x0008), U16_TO_U8S_LE(MS_OS_20_SUBSET_HEADER_FUNCTION),
	ITF_NUM_CDC, 0, U16_TO_U8S_LE(MS_OS_20_DESC_LEN - 18),

	/* DeviceDesc */
	U16_TO_U8S_LE(0x003A), U16_TO_U8S_LE(MS_OS_20_FEATURE_REG_PROPERTY),
	U16_TO_U8S_LE(0x0001), U16_TO_U8S_LE(22),
	'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0,
	'D', 0, 'e', 0, 's', 0, 'c', 0,  0, 0,
	U16_TO_U8S_LE(26),
#if defined(STM32H743xx)
	'R', 0, 'o', 0, 'b', 0, 'o', 0, 't', 0, '7', 0,
	'4', 0, '3', 0, ' ', 0, 'C', 0, 'o', 0, 'm', 0,  0, 0,
#else
	'R', 0, 'o', 0, 'b', 0, 'o', 0, 't', 0, '4', 0,
	'0', 0, '7', 0, ' ', 0, 'C', 0, 'o', 0, 'm', 0,  0, 0,
#endif

	/* FriendlyName */
	U16_TO_U8S_LE(0x003E), U16_TO_U8S_LE(MS_OS_20_FEATURE_REG_PROPERTY),
	U16_TO_U8S_LE(0x0001), U16_TO_U8S_LE(26),
	'F', 0, 'r', 0, 'i', 0, 'e', 0, 'n', 0, 'd', 0,
	'l', 0, 'y', 0, 'N', 0, 'a', 0, 'm', 0, 'e', 0,  0, 0,
	U16_TO_U8S_LE(26),
#if defined(STM32H743xx)
	'R', 0, 'o', 0, 'b', 0, 'o', 0, 't', 0, '7', 0,
	'4', 0, '3', 0, ' ', 0, 'C', 0, 'o', 0, 'm', 0,  0, 0
#else
	'R', 0, 'o', 0, 'b', 0, 'o', 0, 't', 0, '4', 0,
	'0', 0, '7', 0, ' ', 0, 'C', 0, 'o', 0, 'm', 0,  0, 0
#endif
};

TU_VERIFY_STATIC(sizeof(desc_ms_os_20) == MS_OS_20_DESC_LEN, "MS OS 2.0 length");

bool tud_vendor_control_xfer_cb(uint8_t rhport, uint8_t stage,
	tusb_control_request_t const *request)
{
	if (stage != CONTROL_STAGE_SETUP)
		return true;
	if (request->bRequest != USB_VENDOR_CODE)
		return false;
	if (request->wIndex != 7)
		return false;
	return tud_control_xfer(rhport, request, (void *)(uintptr_t)desc_ms_os_20,
		MS_OS_20_DESC_LEN);
}

static char const *string_desc_arr[] = {
	(const char[]){ 0x09, 0x04 },
	"Robo_Grok",
	USB_PRODUCT_NAME,
	USB_SERIAL_NAME,
	USB_PRODUCT_NAME
};

static uint16_t _desc_str[32];

uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
	uint8_t chr_count;
	uint8_t i;

	(void)langid;

	if (index == 0)
	{
		_desc_str[1] = ((uint16_t *)string_desc_arr[0])[0];
		chr_count = 1;
	}
	else
	{
		const char *str;

		if (index >= (sizeof(string_desc_arr) / sizeof(string_desc_arr[0])))
			return 0;
		str = string_desc_arr[index];
		chr_count = (uint8_t)strlen(str);
		if (chr_count > 31)
			chr_count = 31;
		for (i = 0; i < chr_count; i++)
			_desc_str[1 + i] = (uint16_t)((uint8_t)str[i]);
	}

	_desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2u * chr_count + 2u));
	return _desc_str;
}
