#include <stdlib.h>
#include "ppu.h"

static uint8_t _ppu_read(struct device *device, uint16_t address) {
	struct ppu *ppu = (struct ppu *)device;
	return ppu->memory[address & 0x1FFF];
}

static void _ppu_write(struct device *device, uint16_t address, uint8_t value) {
	struct ppu *ppu = (struct ppu *)device;
	ppu->memory[address & 0x1FFF] = value;
}

struct ppu *ppu_new(void) {
	struct ppu *ppu = calloc(1, sizeof(struct ppu));
	ppu->memory = calloc(0x18, sizeof(uint8_t));
	ppu->device.address_from = 0x2000;
	ppu->device.address_to = 0x2007;
	ppu->device.read = &_ppu_read;
	ppu->device.write = &_ppu_write;
	return ppu;
}

void ppu_tick(struct ppu *ppu) {
	(void)ppu;
}

void ppu_destroy(struct ppu *ppu) {
	free(ppu->memory);
	free(ppu);
}