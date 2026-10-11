////////////////////////////////////////////////////////////////////////////////
// TinyUSB CDC HAL — same strategy as Robo_Grok_Core.
// RX bytes go into Hydra ReceiveCharacter() so serialProcessor is unchanged.
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
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

static uint16_t copyTxChunk(char *ring, int indexOut, int indexIn, int count, int size, uint8_t *dst, uint16_t room)
{
	uint16_t contiguous;
	uint16_t copied;

	if ((count <= 0) || (room == 0u)) return 0;
	if (room > 64u) room = 64u; /* one full-speed packet */
	if (indexOut > indexIn)
		contiguous = (uint16_t)(size - indexOut); /* wrapped: send the tail first */
	else
		contiguous = (uint16_t)count;
	copied = contiguous;
	if (copied > room) copied = room;
	memcpy(dst, ring + indexOut, copied);
	return copied;
}

static void commitTxChunk(int *count, int *indexOut, int size, uint16_t written)
{
	*count -= (int)written;
	if (*count < 0) *count = 0;
	*indexOut += (int)written;
	if (*indexOut >= size) *indexOut -= size;
}

/* PrintCheck queues 0x06 into normalTxBuffer. This is the only place that
   copies that buffer onto the USB IN endpoint. Returns immediately. */
static uint16_t sendRing(char *ring, int *count, int *indexOut, int *indexIn, int size)
{
	uint8_t chunk[64];
	uint32_t irqDisabled;
	uint16_t copied;
	uint32_t written;
	uint32_t room;
	int out;
	int in;
	int have;

	room = tud_cdc_write_available();
	if (room > 64u) room = 64u;
	if (room == 0u) return 0;
	irqDisabled = interruptsOff();
	have = *count;
	out = *indexOut;
	in = *indexIn;
	copied = copyTxChunk(ring, out, in, have, size, chunk, (uint16_t)room);
	interruptsOn(irqDisabled);
	if (copied == 0u) return 0;
	written = tud_cdc_write(chunk, copied);
	if (written == 0u) return 0;
	irqDisabled = interruptsOff();
	commitTxChunk(count, indexOut, size, (uint16_t)written);
	interruptsOn(irqDisabled);
	tud_cdc_write_flush();
	return (uint16_t)written;
}

void UsbCdc_Service(void)
{
	uint8_t buf[64];
	uint32_t n;
	uint32_t byteIndex;

	tud_task_ext(0, false); /* empty queue returns immediately */
	UsbCdcConfigured = tud_mounted() ? 1u : 0u;
	usb_was_mounted = UsbCdcConfigured; /* USB does not steal master; UART6 is default */

	n = tud_cdc_available();
	if (n > sizeof(buf)) n = sizeof(buf);
	if (n != 0u)
	{
		n = tud_cdc_read(buf, n);
		for (byteIndex = 0; byteIndex < n; byteIndex++)
		{
			if ((buf[byteIndex] == PING_CHAR) || (buf[byteIndex] == ABORT_CHAR))
				changeMasterCommPort(USB_MASTER);
			if (masterCommPort == USB_MASTER)
				ReceiveCharacter((char)buf[byteIndex]);
			if (COMUSB.RxBuffer.buffer != 0)
			{
				COMUSB.RxBuffer.buffer[COMUSB.RxBuffer.Head] = buf[byteIndex];
				COMUSB.RxBuffer.Head++;
				COMUSB.RxBuffer.Head &= (uint16_t)(COMUSB.RxBuffer.Buffer_Size - 1u); /* wrap Buffer_Size-1 */
				COMUSB.NumberOfCharactersReceived++;
			}
		}
	}

	if (UsbCdcConfigured == 0u) return;
	if ((masterCommPort == USB_MASTER) && (normalTxCharsInBuf > 0))
	{
		sendRing(normalTxBuffer, &normalTxCharsInBuf, &normalTxIndexOut, &normalTxIndexIn, SERIAL_TX_NORMAL_BUFFER_SIZE);
	}
	else if (((_echoProcessedSerialStreamPort | _echoRawSerialStreamPort) == SERIAL_PORT_USB) && (echoTxCharsInBuf > 0))
	{
		sendRing(echoTxBuffer, &echoTxCharsInBuf, &echoTxIndexOut, &echoTxIndexIn, SERIAL_TX_ECHO_BUFFER_SIZE);
	}
}
