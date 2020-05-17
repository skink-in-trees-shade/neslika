#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include "device.h"

struct ppu {
	struct device cpu_device;
	struct device ppu_device;

	uint8_t *memory;
};

struct ppu *ppu_new(void);
void ppu_tick(struct ppu *ppu);
void ppu_destroy(struct ppu *ppu);

#endif