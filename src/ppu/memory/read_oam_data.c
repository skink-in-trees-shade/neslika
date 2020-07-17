#include "ppu/ppu.h"
#include "read_oam_data.h"

uint8_t read_oam_data(void *device, uint16_t address) {
	(void)address;

	struct ppu *ppu = device;
	return ppu->primary_oam[ppu->oam_address];
}