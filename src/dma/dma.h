#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include <stdbool.h>
#include "bus.h"

struct dma {
	struct bus *bus;

	uint16_t cycle;
	uint16_t address;
	uint8_t value;
	bool write_toggle;
};

struct dma *dma_new(struct bus *bus);
void dma_tick(struct dma *dma);
void dma_destroy(struct dma *dma);

#endif