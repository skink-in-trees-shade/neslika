#include "ppu/ppu.h"
#include "write_controller.h"

void write_controller(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct ppu *ppu = device;
	ppu->control = value;
	ppu->temp_vram_address = (ppu->temp_vram_address & 0x73FF) | ((value & 0x03) << 10);
}