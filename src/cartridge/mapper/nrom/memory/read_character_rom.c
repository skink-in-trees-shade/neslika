#include "cartridge/cartridge.h"
#include "read_character_rom.h"

uint8_t nrom_read_character_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	return cartridge->chr_rom[address];
}