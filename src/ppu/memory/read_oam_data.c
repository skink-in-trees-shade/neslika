#include "ppu/ppu.h"
#include "read_oam_data.h"

uint8_t read_oam_data(void *device, uint16_t address) {
	(void)address;

	struct ppu *ppu = device;
	uint8_t value = ppu->primary_oam[ppu->oam_address];
	ppu->last_value = value;

	if ((ppu->oam_address & 0x03) == 0x02) {
		ppu->last_value_decay = 0;
		return value & 0xE3;
	}

	return value;
}