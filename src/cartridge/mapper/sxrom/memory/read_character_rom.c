#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "read_character_rom.h"

uint8_t sxrom_read_character_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;

	uint8_t bank = sxrom->chr_rom_bank[(address & 0x1000) >> 12];
	return cartridge->chr_rom[(bank << 12) | (address & 0x0FFF)];
}