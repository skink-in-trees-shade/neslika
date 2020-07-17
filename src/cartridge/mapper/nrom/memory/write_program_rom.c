#include "cartridge/cartridge.h"
#include "write_program_rom.h"

void nrom_write_program_rom(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	address &= 0x4000 * cartridge->prg_rom_count - 1;
	cartridge->prg_rom[address] = value;
}