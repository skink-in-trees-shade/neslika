#include "cartridge/cartridge.h"
#include "cartridge/mapper/cnrom/cnrom.h"
#include "select_chr_rom_bank.h"

void cnrom_select_chr_rom_bank(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct cnrom *cnrom = cartridge->mapper_data;

	cnrom->chr_rom_bank = value & 0x03;
}