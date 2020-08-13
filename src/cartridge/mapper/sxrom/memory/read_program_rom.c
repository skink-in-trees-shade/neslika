#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "read_program_rom.h"

uint8_t sxrom_read_program_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;

	uint8_t bank = sxrom->prg_rom_bank[(address & 0x4000) >> 14];
	return cartridge->prg_rom[(bank << 14) | (address & 0x3FFF)];
}