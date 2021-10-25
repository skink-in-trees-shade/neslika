#include "cartridge/cartridge.h"
#include "cartridge/mapper/bxrom/bxrom.h"
#include "write_program_ram.h"

void bxrom_write_program_ram(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct bxrom *bxrom = cartridge->mapper_data;
	bxrom->prg_ram[address & 0x1FFF] = value;
}