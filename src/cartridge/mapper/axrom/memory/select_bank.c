#include "cartridge/cartridge.h"
#include "cartridge/mapper/axrom/axrom.h"
#include "select_bank.h"

void axrom_select_bank(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct axrom *axrom = cartridge->mapper_data;
	axrom->prg_rom_bank = value & 0x07;
	axrom->name_table_bank = (value & 0x10) >> 4;
}