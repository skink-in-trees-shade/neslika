#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "read_name_table.h"

uint8_t sxrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;

	if (sxrom->mirroring != sxrom_mirroring_vertical) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	return sxrom->name_table[address & 0x07FF];
}