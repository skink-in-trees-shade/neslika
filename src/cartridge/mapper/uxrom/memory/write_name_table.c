#include "cartridge/cartridge.h"
#include "cartridge/mapper/uxrom/uxrom.h"
#include "write_name_table.h"

void uxrom_write_name_table(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct uxrom *uxrom = cartridge->mapper_data;

	if (!cartridge->vertical_mirroring) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	uxrom->name_table[address & 0x07FF] = value;
}