#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "read_name_table.h"

uint8_t txrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct txrom *txrom = cartridge->mapper_data;

	bool a12 = (address & 0x1000) == 0x1000;
	if (!txrom->a12 && a12) {
		if (txrom->irq_counter == 0x00) {
			txrom->irq_counter = txrom->irq_reload;
		} else {
			txrom->irq_counter--;
		}

		if (txrom->irq_counter == 0x00 && txrom->irq_enabled) {
			cartridge->irq_occured = true;
		}
	}
	txrom->a12 = a12;

	if (!cartridge->vertical_mirroring) {
		address = ((address & 0x0800) >> 1) | (address & 0x03FF);
	}

	return txrom->name_table[address & 0x07FF];
}