#include "ppu/ppu.h"
#include "write_mask.h"

void write_mask(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	ppu->mask = value;
	ppu->last_value = value;
}