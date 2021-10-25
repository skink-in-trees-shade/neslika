#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "read_name_table.h"

uint8_t bxrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;

	if (!cartridge->vertical_mirroring) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	return bxrom->name_table[address & 0x07FF];
}