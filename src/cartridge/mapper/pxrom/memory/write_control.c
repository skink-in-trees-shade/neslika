#include "cartridge/cartridge.h"
#include "write_control.h"

void pxrom_write_control(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct cartridge *cartridge = device;
	cartridge->vertical_mirroring = (value & 0x01) == 0x00;
}