#include "ppu/ppu.h"
#include "write_palette_table.h"

void write_palette_table(void *device, uint16_t address, uint8_t value) {
	struct ppu *ppu = device;
	address &= 0x001F;
	if ((address & 0x0013) == 0x0010) {
		address &= 0x000F;
	}
	ppu->palette_table[address] = value;
}