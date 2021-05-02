#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "read_irq_status.h"

uint8_t exrom_read_irq_status(void *device, uint16_t address) {
	(void)address;

	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	uint8_t value = 0
		| (exrom->in_frame << 6)
		| (exrom->irq_pending << 7);
	exrom->irq_pending = false;
	cartridge->irq_occured = false;
	return value;
}