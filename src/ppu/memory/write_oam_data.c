#include "ppu/ppu.h"
#include "write_oam_data.h"

void write_oam_data(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	if ((ppu->oam_address & 0x03) == 0x02) {
		value &= 0xE3;
	}
	ppu->primary_oam[ppu->oam_address++] = value;
}