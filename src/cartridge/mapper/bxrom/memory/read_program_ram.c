#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "read_program_ram.h"

uint8_t bxrom_read_program_ram(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;
	return bxrom->prg_ram[address & 0x1FFF];
}