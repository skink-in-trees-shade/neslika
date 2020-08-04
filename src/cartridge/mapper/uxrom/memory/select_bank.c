#include "cartridge/cartridge.h"
#include "select_bank.h"

void uxrom_select_bank(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	cartridge->prg_rom_bank = value & 0x0F;
}