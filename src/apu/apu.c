#include <stdlib.h>
#include "apu.h"

struct apu {
	struct bus *bus;
};

struct apu *apu_new(struct bus *bus) {
	struct apu *apu = calloc(1, sizeof(struct apu));
	apu->bus = bus;
	return apu;
}

void apu_tick(struct apu *apu) {
	(void)apu;
}

void apu_destroy(struct apu *apu) {
	free(apu);
}