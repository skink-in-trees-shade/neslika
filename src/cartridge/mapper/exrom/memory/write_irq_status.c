#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "write_irq_status.h"

void exrom_write_irq_status(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	exrom->irq_enabled = (value & 0x80) == 0x80;
	if (exrom->irq_enabled && exrom->irq_pending) {
		cartridge->irq_occured = true;
	}
}