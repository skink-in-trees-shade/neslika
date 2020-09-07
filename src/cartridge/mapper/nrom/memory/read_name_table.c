#include "cartridge/cartridge.h"
#include "cartridge/mapper/nrom/nrom.h"
#include "read_name_table.h"

uint8_t nrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct nrom *nrom = cartridge->mapper_data;

	if (!cartridge->vertical_mirroring) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	return nrom->name_table[address & 0x07FF];
}