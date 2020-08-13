#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "select_prg_rom_bank.h"

void sxrom_select_prg_rom_bank(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;

	if ((value & 0x80) == 0x80) {
		sxrom->shift = 0x10;
		sxrom->control |= 0x0C;
	} else {
		bool shift_full = sxrom->shift & 0x01;
		sxrom->shift = ((value & 0x01) << 4) | (sxrom->shift >> 1);

		if (shift_full) {
			switch ((sxrom->control & 0x0C) >> 2) {
				case 0x00:
				case 0x01:
					sxrom->prg_rom_bank[0] = (sxrom->shift & 0x0E) << 1;
					sxrom->prg_rom_bank[1] = sxrom->prg_rom_bank[0] + 1;
				break;

				case 0x02:
					sxrom->prg_rom_bank[0] = 0;
					sxrom->prg_rom_bank[1] = sxrom->shift & 0x0F;
				break;

				case 0x03:
					sxrom->prg_rom_bank[0] = sxrom->shift & 0x0F;
					sxrom->prg_rom_bank[1] = cartridge->prg_rom_count - 1;
				break;
			}

			sxrom->shift = 0x10;
		}
	}
}