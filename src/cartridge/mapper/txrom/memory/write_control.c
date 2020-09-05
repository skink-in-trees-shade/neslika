#include "cartridge/cartridge.h"
#include "write_control.h"

void txrom_write_control(void *device, uint16_t address, uint8_t value) {
	struct cartridge *cartridge = device;

	if ((address & 0x0001) == 0x0000) {
		cartridge->vertical_mirroring = (value & 0x01) == 0x00;
	}
}