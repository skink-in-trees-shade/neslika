#include "ppu/ppu.h"
#include "write_oam_address.h"

void write_oam_address(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	ppu->oam_address = value;
}