#include <stddef.h>
#include <stdlib.h>
#include "apu.h"

static uint8_t _apu_read(struct device *device, uint16_t address) {
	struct apu *apu = (struct apu *)((char *)device - offsetof(struct apu, device));
	return apu->memory[address & 0x3FFF];
}

static void _apu_write(struct device *device, uint16_t address, uint8_t value) {
	struct apu *apu = (struct apu *)((char *)device - offsetof(struct apu, device));
	apu->memory[address & 0x3FFF] = value;
}

struct apu *apu_new(void) {
	struct apu *apu = calloc(1, sizeof(struct apu));
	apu->memory = calloc(0x18, sizeof(uint8_t));
	apu->device.address_from = 0x4000;
	apu->device.address_to = 0x4007;
	apu->device.read = &_apu_read;
	apu->device.write = &_apu_write;
	return apu;
}

void apu_tick(struct apu *apu) {
	(void)apu;
}

void apu_destroy(struct apu *apu) {
	free(apu->memory);
	free(apu);
}