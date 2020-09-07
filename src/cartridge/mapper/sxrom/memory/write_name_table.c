#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "write_name_table.h"

void sxrom_write_name_table(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;

	if (sxrom->mirroring != sxrom_mirroring_vertical) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	sxrom->name_table[address & 0x07FF] = value;
}