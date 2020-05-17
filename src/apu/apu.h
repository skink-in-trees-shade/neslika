#ifndef APU_H
#define APU_H

#include <stdint.h>
#include "device.h"

struct apu {
	struct device device;

	uint8_t *memory;
};

struct apu *apu_new(void);
void apu_destroy(struct apu *apu);

#endif