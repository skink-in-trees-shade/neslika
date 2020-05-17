#include "nrom.h"

uint16_t nrom_cpu(struct cartridge *cartridge, uint16_t address) {
	return cartridge->prg_rom_count == 1
		? address & 0x3FFF
		: address & 0x7FFF;
}

uint16_t nrom_ppu(struct cartridge *cartridge, uint16_t address) {
	(void)cartridge;
	return address;
}