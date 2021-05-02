#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "select_irq_scanline.h"

void exrom_select_irq_scanline(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;
	exrom->irq_scanline = value;
}