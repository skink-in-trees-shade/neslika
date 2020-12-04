#include "cartridge/cartridge.h"
#include "cartridge/mapper/pxrom/pxrom.h"
#include "read_program_ram.h"

uint8_t pxrom_read_program_ram(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct pxrom *pxrom = cartridge->mapper_data;
	return pxrom->prg_ram[address & 0x1FFF];
}