#include "cartridge/cartridge.h"
#include "cartridge/mapper/pxrom/pxrom.h"
#include "select_chr_rom_bank.h"

void pxrom_select_chr_rom_bank(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct pxrom *pxrom = cartridge->mapper_data;

	uint8_t bank = ((address - 0xB000) & 0x2000) >> 13;
	uint8_t latch = (~address & 0x1000) >> 12;
	pxrom->chr_rom_bank[bank][latch] = value & 0x1F;
}