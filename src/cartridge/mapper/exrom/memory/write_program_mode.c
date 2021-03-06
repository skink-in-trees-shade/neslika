#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "write_program_mode.h"

void exrom_write_program_mode(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;
	exrom->prg_mode = value & 0x03;
}