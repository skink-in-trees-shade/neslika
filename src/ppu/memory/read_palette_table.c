#include "ppu/ppu.h"
#include "read_palette_table.h"

uint8_t read_palette_table(void *device, uint16_t address) {
	struct ppu *ppu = device;
	address &= 0x001F;
	if ((address & 0x0013) == 0x0010) {
		address &= 0x000F;
	}
	return ppu->palette_table[address];
}