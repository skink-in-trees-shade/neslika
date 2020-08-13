#include "ppu/ppu.h"
#include "read_name_table.h"

uint8_t read_name_table(void *device, uint16_t address) {
	struct ppu *ppu = device;
	if (ppu->cartridge->mirroring == mirroring_horizontal) {
		address = (address & 0x03FF) | ((address & 0x0800) >> 1);
	}
	address &= 0x07FF;
	return ppu->name_table[address];
}