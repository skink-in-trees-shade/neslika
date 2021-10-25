#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "write_character_rom.h"

void bxrom_write_character_rom(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;
	cartridge->chr_rom[(bxrom->chr_rom_bank[address >> 12] << 12) | (address & 0x0FFF)] = value;
}