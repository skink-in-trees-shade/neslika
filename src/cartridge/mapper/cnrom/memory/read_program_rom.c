#include "cartridge/cartridge.h"
#include "read_program_rom.h"

uint8_t cnrom_read_program_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	address &= 0x4000 * cartridge->prg_rom_count - 1;
	return cartridge->prg_rom[address];
}