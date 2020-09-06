#ifndef APU_H
#define APU_H

#include <stdint.h>
#include <stdbool.h>
#include "platform/audio.h"
#include "bus.h"
#include "pulse/pulse.h"
#include "triangle/triangle.h"
#include "noise/noise.h"

struct apu {
	struct bus *bus;
	struct audio *audio;

	struct pulse *pulse[2];
	struct triangle *triangle;
	struct noise *noise;

	uint16_t cycle;
	bool extra_frame_step;
};

struct apu *apu_new(struct bus *bus, struct audio *audio);
void apu_tick(struct apu *apu);
void apu_destroy(struct apu *apu);

#endif