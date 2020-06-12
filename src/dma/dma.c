#include <stddef.h>
#include <stdlib.h>
#include "dma.h"

static uint8_t _dma_read(struct device *device, uint16_t address) {
	(void)device;
	(void)address;
	return 0x00;
}

static void _dma_write(struct device *device, uint16_t address, uint8_t value) {
	struct dma *dma = (struct dma *)((char *)device - offsetof(struct dma, device));
	
	if (address == 0x4014) {
		dma->cycle = 0x00;
		dma->page = value;
		dma->address = 0x00;
		dma->write_toggle = true;
	}
}

struct dma *dma_new(void) {
	struct dma *dma = calloc(1, sizeof(struct dma));
	dma->device.address_from = 0x4014;
	dma->device.address_to = 0x4014;
	dma->device.read = &_dma_read;
	dma->device.write = &_dma_write;
	return dma;
}

void dma_tick(struct dma *dma) {
	if (dma->write_toggle) {
		if (dma->cycle % 2 == 0) {
			uint16_t address = (dma->page << 8) | dma->address;
			dma->value = bus_read(dma->bus, address);
		} else {
			if (dma->address == 0xFF) {
				dma->write_toggle = false;
			}

			dma->ppu->primary_oam[dma->address++] = dma->value;
		}

		dma->cycle++;
	}
}

void dma_destroy(struct dma *dma) {
	free(dma);
}