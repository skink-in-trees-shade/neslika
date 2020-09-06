#include "cartridge/cartridge.h"
#include "cartridge/mapper/axrom/axrom.h"
#include "read_name_table.h"

uint8_t axrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct axrom *axrom = cartridge->mapper_data;
	return axrom->name_table[(axrom->name_table_bank << 10) | (address & 0x03FF)];
}