#include "cartridge/cartridge.h"
#include "cartridge/mapper/exrom/exrom.h"
#include "read_name_table.h"

uint8_t exrom_read_name_table(void *device, uint16_t address) {
	struct cartridge *cartridge = device;
	struct exrom *exrom = cartridge->mapper_data;

	exrom->name_table_fetch_count++;
	if (exrom->name_table_fetch_count == 63) {
		exrom->use_background_banks = false;
	} else if (exrom->name_table_fetch_count == 64) {
		exrom->use_background_banks = true;
	}

	if (address == exrom->last_address) {
		exrom->address_match_count++;
		if (exrom->address_match_count == 2) {
			if (!exrom->in_frame) {
				exrom->in_frame = true;
				exrom->scanline_counter = 0;
				exrom->irq_pending = false;
			} else {
				exrom->name_table_fetch_count = 0;
				exrom->use_background_banks = true;
				exrom->scanline_counter++;
				if (exrom->scanline_counter == exrom->irq_scanline) {
					exrom->irq_pending = true;
					if (exrom->irq_enabled) {
						cartridge->irq_occured = true;
					}
				}
			}
		}
	} else {
		exrom->address_match_count = 0;
	}
	exrom->last_address = address;

	switch (exrom->mirroring[(address & 0x0C00) >> 10]) {
		case 0x00:
			return exrom->name_table[address & 0x03FF];
		break;

		case 0x01:
			return exrom->name_table[0x0400 | (address & 0x03FF)];
		break;

		case 0x03:
			return (address & 0x03FF) >= 0x03C0
				? exrom->fill_palette
				: exrom->fill_tile;
		break;
	}

	return 0x00;
}