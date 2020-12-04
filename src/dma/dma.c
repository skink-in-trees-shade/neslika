#include <stdlib.h>
#include "memory/write_oam_dma.h"
#include "dma.h"

struct dma *dma_new(struct bus *bus) {
	struct dma *dma = calloc(1, sizeof(struct dma));

	dma->bus = bus;
	bus_register(dma->bus, dma, 0x4014, 0x4014, NULL, &write_oam_dma);

	return dma;
}

void dma_tick(struct dma *dma) {
	if (dma->cycle % 2 == 0) {
		dma->value = bus_read(dma->bus, dma->address++);
	} else {
		bus_write(dma->bus, 0x2004, dma->value);
	}

	dma->cycle++;

	if (dma->cycle == 0x201) {
		dma->write_toggle = false;
	}
}

void dma_destroy(struct dma *dma) {
	free(dma);
}