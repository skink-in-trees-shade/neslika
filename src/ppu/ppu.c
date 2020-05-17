#include <stdlib.h>
#include "ppu.h"

static uint8_t _ppu_cpu_read(struct device *device, uint16_t address) {
	struct ppu *ppu = (struct ppu *)device;
	return ppu->memory[address & 0x1FFF];
}

static void _ppu_cpu_write(struct device *device, uint16_t address, uint8_t value) {
	struct ppu *ppu = (struct ppu *)device;
	ppu->memory[address & 0x1FFF] = value;
}

static uint8_t _ppu_ppu_read(struct device *device, uint16_t address) {
	struct ppu *ppu = (struct ppu *)device;
	return ppu->memory[address & 0x1FFF];
}

static void _ppu_ppu_write(struct device *device, uint16_t address, uint8_t value) {
	struct ppu *ppu = (struct ppu *)device;
	ppu->memory[address & 0x1FFF] = value;
}

struct ppu *ppu_new(void) {
	struct ppu *ppu = calloc(1, sizeof(struct ppu));
	ppu->memory = calloc(0x18, sizeof(uint8_t));

	ppu->cpu_device.address_from = 0x2000;
	ppu->cpu_device.address_to = 0x2007;
	ppu->cpu_device.read = &_ppu_cpu_read;
	ppu->cpu_device.write = &_ppu_cpu_write;

	ppu->ppu_device.address_from = 0x2000;
	ppu->ppu_device.address_to = 0x2007;
	ppu->ppu_device.read = &_ppu_ppu_read;
	ppu->ppu_device.write = &_ppu_ppu_write;

	return ppu;
}

void ppu_tick(struct ppu *ppu) {
	(void)ppu;
}

void ppu_destroy(struct ppu *ppu) {
	free(ppu->memory);
	free(ppu);
}