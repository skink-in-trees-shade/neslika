#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "read_program_ram.h"

uint8_t sxrom_read_program_ram(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;
	return sxrom->prg_ram[address & 0x1FFF];
}