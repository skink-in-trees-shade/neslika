#include "nrom.h"

uint8_t nrom_cpu_read(struct cartridge *cartridge, uint16_t address) {
	address &= 0x4000 * cartridge->prg_rom_count - 1;
	return cartridge->prg_rom[address];
}

void nrom_cpu_write(struct cartridge *cartridge, uint16_t address, uint8_t value) {
	address &= 0x4000 * cartridge->prg_rom_count - 1;
	cartridge->prg_rom[address] = value;
}

uint8_t nrom_ppu_read(struct cartridge *cartridge, uint16_t address) {
	return cartridge->chr_rom[address];
}

void nrom_ppu_write(struct cartridge *cartridge, uint16_t address, uint8_t value) {
	cartridge->chr_rom[address] = value;
}