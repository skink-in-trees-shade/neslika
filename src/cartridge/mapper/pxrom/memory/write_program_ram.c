#include "cartridge/cartridge.h"
#include "cartridge/mapper/pxrom/pxrom.h"
#include "write_program_ram.h"

void pxrom_write_program_ram(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct pxrom *pxrom = cartridge->mapper_data;
	pxrom->prg_ram[address & 0x1FFF] = value;
}