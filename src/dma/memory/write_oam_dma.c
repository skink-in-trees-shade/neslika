#include "dma/dma.h"
#include "write_oam_dma.h"

void write_oam_dma(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct dma *dma = device;
	dma->cycle = 0x00;
	dma->address = value << 8;
	dma->write_toggle = true;
}