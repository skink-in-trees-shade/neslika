#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "write_name_table.h"

void exrom_write_name_table(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	switch (exrom->mirroring[(address & 0x0C00) >> 10]) {
		case 0x00:
			exrom->name_table[address & 0x03FF] = value;
		break;

		case 0x01:
			exrom->name_table[0x0400 | (address & 0x03FF)] = value;
		break;
	}
}