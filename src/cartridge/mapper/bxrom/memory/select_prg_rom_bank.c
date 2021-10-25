#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "select_prg_rom_bank.h"

void bxrom_select_prg_rom_bank(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;
	bxrom->prg_rom_bank = value;
}