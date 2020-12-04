#include "cartridge/cartridge.h"
#include "cartridge/mapper/pxrom/pxrom.h"
#include "read_name_table.h"

uint8_t pxrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct pxrom *pxrom = cartridge->mapper_data;

	if (!cartridge->vertical_mirroring) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	return pxrom->name_table[address & 0x07FF];
}