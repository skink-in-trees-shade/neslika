#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "write_program_ram.h"

void sxrom_write_program_ram(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;
	sxrom->prg_ram[address & 0x1FFF] = value;
}