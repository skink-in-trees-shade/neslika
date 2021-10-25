#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "read_character_rom.h"

uint8_t bxrom_read_character_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;
	return cartridge->chr_rom[(bxrom->chr_rom_bank[address >> 12] << 12) | (address & 0x0FFF)];
}