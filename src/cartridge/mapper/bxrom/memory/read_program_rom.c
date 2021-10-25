#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "read_program_rom.h"

uint8_t bxrom_read_program_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;
	return cartridge->prg_rom[(bxrom->prg_rom_bank << 15) | (address & 0x7FFF)];
}