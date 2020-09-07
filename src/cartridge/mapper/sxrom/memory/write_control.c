#include "cartridge/cartridge.h"
#include "cartridge/mapper/sxrom/sxrom.h"
#include "write_control.h"

void sxrom_write_control(void *device, uint16_t address, uint8_t value) {
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
			sxrom->control = sxrom->shift & 0x1F;
			sxrom->mirroring = sxrom->control & 0x03;

			sxrom->shift = 0x10;
		}
	}
}