#include "cartridge/cartridge.h"
#include "cartridge/mapper/pxrom/pxrom.h"
#include "select_prg_rom_bank.h"

void pxrom_select_prg_rom_bank(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct pxrom *pxrom = cartridge->mapper_data;
	pxrom->prg_rom_bank[0] = value & 0x0F;
}