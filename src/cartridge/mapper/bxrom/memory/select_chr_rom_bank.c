#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "select_chr_rom_bank.h"

void bxrom_select_chr_rom_bank(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;
	bxrom->chr_rom_bank[address & 0x01] = value & 0x0F;
}