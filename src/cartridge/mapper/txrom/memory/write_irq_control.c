#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "write_irq_control.h"

void txrom_write_irq_control(void *device, uint16_t address, uint8_t value) {
	(void)value;

	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;
	txrom->irq_enabled = address & 0x0001;
	if (!txrom->irq_enabled) {
		cartridge->irq_occured = false;
	}
}