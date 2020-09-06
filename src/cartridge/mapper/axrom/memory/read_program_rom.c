#include "cartridge/cartridge.h"
#include "cartridge/mapper/axrom/axrom.h"
#include "read_program_rom.h"

uint8_t axrom_read_program_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct axrom *axrom = cartridge->mapper_data;
	return cartridge->prg_rom[(axrom->prg_rom_bank << 15) | (address & 0x7FFF)];
}