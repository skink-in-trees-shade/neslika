#include "cartridge/cartridge.h"
#include "cartridge/mapper/uxrom/uxrom.h"
#include "select_bank.h"

void uxrom_select_bank(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct uxrom *uxrom = cartridge->mapper_data;
	uxrom->prg_rom_bank = value & 0x0F;
}