#include "cartridge/cartridge.h"
#include "cartridge/mapper/txrom/txrom.h"
#include "read_character_rom.h"

uint8_t txrom_read_character_rom(void *device, uint16_t address) {
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

	uint8_t bank = txrom->chr_rom_bank[(address & 0x1C00) >> 10];
	return cartridge->chr_rom[(bank << 10) | (address & 0x03FF)];
}