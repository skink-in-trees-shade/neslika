#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "write_program_ram.h"

void txrom_write_program_ram(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;
	txrom->prg_ram[address & 0x1FFF] = value;
}