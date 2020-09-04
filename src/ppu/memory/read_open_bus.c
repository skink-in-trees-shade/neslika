#include "ppu/ppu.h"
#include "read_open_bus.h"

uint8_t read_open_bus(void *device, uint16_t address) {
	(void)address;

	struct ppu *ppu = device;
	return ppu->last_value;
}