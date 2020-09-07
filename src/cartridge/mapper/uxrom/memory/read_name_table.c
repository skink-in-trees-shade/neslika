#include "cartridge/cartridge.h"
#include "cartridge/mapper/uxrom/uxrom.h"
#include "read_name_table.h"

uint8_t uxrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct uxrom *uxrom = cartridge->mapper_data;

	if (!cartridge->vertical_mirroring) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	return uxrom->name_table[address & 0x07FF];
}