#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "read_program_rom.h"

uint8_t txrom_read_program_rom(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;

	uint8_t bank = txrom->prg_rom_bank[(address & 0x6000) >> 13];
	return cartridge->prg_rom[(bank << 13) | (address & 0x1FFF)];
}