#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "write_mirroring.h"

void exrom_write_mirroring(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	exrom->mirroring[0] = value & 0x03;
	exrom->mirroring[1] = (value & 0x0C) >> 2;
	exrom->mirroring[2] = (value & 0x30) >> 4;
	exrom->mirroring[3] = (value & 0xC0) >> 6;
}