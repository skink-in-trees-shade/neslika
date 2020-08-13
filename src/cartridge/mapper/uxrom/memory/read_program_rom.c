#include "cartridge/cartridge.h"
#include "cartridge/mapper/uxrom/uxrom.h"
#include "read_program_rom.h"

uint8_t uxrom_read_program_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct uxrom *uxrom = cartridge->mapper_data;
	uint8_t bank = address >= 0xC000 ? cartridge->prg_rom_count - 1 : uxrom->prg_rom_bank;
	return cartridge->prg_rom[(bank << 14) | (address & 0x3FFF)];
}