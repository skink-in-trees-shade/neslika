#include "cartridge/cartridge.h"
#include "write_character_rom.h"

void nrom_write_character_rom(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	cartridge->chr_rom[address] = value;
}