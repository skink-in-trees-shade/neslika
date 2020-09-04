#include "ppu/ppu.h"
#include "write_open_bus.h"

void write_open_bus(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	ppu->last_value = value;
}