#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "write_fill_palette.h"

void exrom_write_fill_palette(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	uint8_t color = value & 0x03;
	exrom->fill_palette = (color << 6) | (color << 4) | (color << 2) | color;
}