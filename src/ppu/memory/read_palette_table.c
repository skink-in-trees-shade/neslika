#include "ppu/ppu.h"
#include "read_palette_table.h"

uint8_t read_palette_table(void *device, uint16_t address) {
	struct ppu *ppu = device;
	address &= 0x001F;
	if ((address & 0x0013) == 0x0010) {
		address &= 0x000F;
	}

	uint8_t color = ppu->palette_table[address];
	if ((ppu->mask & 0x01) == 0x01) {
		color &= 0x30;
	}
	return color;
}