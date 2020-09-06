#include "cartridge/cartridge.h"
#include "cartridge/mapper/axrom/axrom.h"
#include "write_name_table.h"

void axrom_write_name_table(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct axrom *axrom = cartridge->mapper_data;
	axrom->name_table[(axrom->name_table_bank << 10) | (address & 0x03FF)] = value;
}