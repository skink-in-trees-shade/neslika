#include "ppu/ppu.h"
#include "write_name_table.h"

void write_name_table(void *device, uint16_t address, uint8_t value) {
	struct ppu *ppu = device;
	if (!ppu->cartridge->vertical_mirroring) {
		address = (address & 0x03FF) | ((address & 0x0800) >> 1);
	}
	address &= 0x07FF;
	ppu->name_table[address] = value;
}