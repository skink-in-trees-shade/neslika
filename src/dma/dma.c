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
		dma->cpu_address = value << 8;
		dma->ppu_address = dma->ppu->oam_address;
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
			dma->value = bus_read(dma->bus, dma->cpu_address++);
		} else {
			dma->ppu->primary_oam[dma->ppu_address++] = dma->value;
		}

		dma->cycle++;
		dma->cpu->cycle++;

		if (dma->cycle == 0x201) {
			dma->write_toggle = false;
		}
	}
}

void dma_destroy(struct dma *dma) {
	free(dma);
}