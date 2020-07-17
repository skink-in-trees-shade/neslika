#include "ppu/ppu.h"
#include "write_oam_data.h"

void write_oam_data(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	ppu->primary_oam[ppu->oam_address++] = value;
}