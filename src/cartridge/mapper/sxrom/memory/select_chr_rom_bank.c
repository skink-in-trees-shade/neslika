#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "select_chr_rom_bank.h"

void sxrom_select_chr_rom_bank(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;
	struct sxrom *sxrom = cartridge->mapper_data;

	if ((value & 0x80) == 0x80) {
		sxrom->shift = 0x10;
		sxrom->control |= 0x0C;
	} else {
		bool shift_full = sxrom->shift & 0x01;
		sxrom->shift = ((value & 0x01) << 4) | (sxrom->shift >> 1);

		if (shift_full) {
			switch ((sxrom->control & 0x10) >> 4) {
				case 0x00:
					sxrom->chr_rom_bank[0] = (sxrom->shift & 0x1E) << 1;
					sxrom->chr_rom_bank[1] = sxrom->chr_rom_bank[0] + 1;
				break;

				case 0x01:
					sxrom->chr_rom_bank[(address & 0x4000) >> 14] = sxrom->shift & 0x1F;
				break;
			}

			sxrom->shift = 0x10;
		}
	}
}