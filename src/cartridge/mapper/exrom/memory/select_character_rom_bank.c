#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "select_character_rom_bank.h"

void exrom_select_character_rom_bank(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	uint8_t bank = address & 0x0F;
	exrom->chr_rom_bank[bank] = value;
	exrom->use_background_banks = bank > 0x07;
}