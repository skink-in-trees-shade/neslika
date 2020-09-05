#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "read_program_ram.h"

uint8_t txrom_read_program_ram(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;
	return txrom->prg_ram[address & 0x1FFF];
}