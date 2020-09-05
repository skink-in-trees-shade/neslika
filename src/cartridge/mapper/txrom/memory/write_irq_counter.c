#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "write_irq_counter.h"

void txrom_write_irq_counter(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;

	if ((address & 0x0001) == 0x0000) {
		txrom->irq_reload = value;
	} else {
		txrom->irq_counter = 0x00;
	}
}