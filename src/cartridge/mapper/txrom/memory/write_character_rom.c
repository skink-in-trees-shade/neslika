#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "write_character_rom.h"

void txrom_write_character_rom(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;

	uint8_t bank = txrom->chr_rom_bank[(address & 0x1C00) >> 10];
	cartridge->chr_rom[(bank << 10) | (address & 0x03FF)] = value;
}