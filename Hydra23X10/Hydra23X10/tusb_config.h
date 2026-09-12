#pragma once
#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef STM32H743xx
#define CFG_TUSB_MCU          OPT_MCU_STM32H7
#else
#define CFG_TUSB_MCU          OPT_MCU_STM32F4
/* Hydra cmsis stm32f4xx.h has no USB_OTG_FS_MAX_* — TinyUSB dwc2 needs them */
#ifndef USB_OTG_FS_MAX_IN_ENDPOINTS
#define USB_OTG_FS_MAX_IN_ENDPOINTS   4U
#define USB_OTG_FS_MAX_OUT_ENDPOINTS  4U
#define USB_OTG_FS_TOTAL_FIFO_SIZE    1280U
#define USB_OTG_HS_MAX_IN_ENDPOINTS   6U
#define USB_OTG_HS_MAX_OUT_ENDPOINTS  6U
#define USB_OTG_HS_TOTAL_FIFO_SIZE    4096U
#endif
#endif

#define CFG_TUSB_OS           OPT_OS_NONE
#define CFG_TUSB_DEBUG        0

#define BOARD_TUD_RHPORT      0
#define BOARD_TUD_MAX_SPEED   OPT_MODE_FULL_SPEED

#define CFG_TUSB_RHPORT0_MODE (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)
#define CFG_TUD_ENABLED       1
#define CFG_TUD_MAX_SPEED     BOARD_TUD_MAX_SPEED

#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION
#endif
#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN    __attribute__((aligned(4)))
#endif

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE 64
#endif

#define CFG_TUD_CDC            1
#define CFG_TUD_MSC            0
#define CFG_TUD_HID            0
#define CFG_TUD_MIDI           0
#define CFG_TUD_VENDOR         0

#define CFG_TUD_CDC_RX_BUFSIZE 256
#define CFG_TUD_CDC_TX_BUFSIZE 256
#define CFG_TUD_CDC_EP_BUFSIZE 64

#endif
