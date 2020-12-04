#include "cartridge/cartridge.h"
#include "cartridge/mapper/pxrom/pxrom.h"
#include "write_character_rom.h"

void pxrom_write_character_rom(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct pxrom *pxrom = cartridge->mapper_data;

	uint8_t latch = pxrom->chr_rom_latch[(address & 0x1000) >> 12];
	uint8_t bank = pxrom->chr_rom_bank[(address & 0x1000) >> 12][latch];
	cartridge->chr_rom[(bank << 12) | (address & 0x0FFF)] = value;
}