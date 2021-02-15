#include <stdlib.h>
#include "memory/read_control.h"
#include "memory/write_control.h"
#include "memory/write_frame.h"
#include "apu.h"

struct apu *apu_new(struct bus *bus, struct audio *audio) {
	struct apu *apu = calloc(1, sizeof(struct apu));

	apu->bus = bus;
	apu->audio = audio;
	apu->pulse[0] = pulse_new(apu->bus, 1);
	apu->pulse[1] = pulse_new(apu->bus, 2);
	apu->triangle = triangle_new(apu->bus);
	apu->noise = noise_new(apu->bus);

	bus_register(apu->bus, apu, 0x4015, 0x4015, &read_control, &write_control);
	bus_register(apu->bus, apu, 0x4017, 0x4017, NULL, &write_frame);

	return apu;
}

void apu_tick(struct apu *apu) {
	if (apu->cycle % 2 == 0) {
		pulse_tick(apu->pulse[0]);
		pulse_tick(apu->pulse[1]);
	}
	triangle_tick(apu->triangle);
	noise_tick(apu->noise);

	uint16_t frame_length = apu->extra_frame_step ? 37282 : 29830;
	if (apu->cycle == 14914 || apu->cycle == frame_length) {
		pulse_half_frame_tick(apu->pulse[0]);
		pulse_half_frame_tick(apu->pulse[1]);
		triangle_half_frame_tick(apu->triangle);
		noise_half_frame_tick(apu->noise);
	}

	if (!apu->irq_inhibit && !apu->extra_frame_step && apu->cycle == frame_length) {
		apu->irq_occured = true;
	}

	double pulse_output = 0.00752 * (pulse_sample(apu->pulse[0]) + pulse_sample(apu->pulse[1]));
	double tnd_output = 0.00851 * triangle_sample(apu->triangle) + 0.00494 * noise_sample(apu->noise);
	double sample = pulse_output + tnd_output;
	audio_sample(apu->audio, sample);

	apu->cycle++;
	if (apu->cycle == frame_length + 1) {
		apu->cycle = 0;
	}

	if (apu->reset_cycle > 0) {
		apu->reset_cycle--;
		if (apu->reset_cycle == 0) {
			apu->cycle = 0;
		}
	}
}

void apu_destroy(struct apu *apu) {
	noise_destroy(apu->noise);
	triangle_destroy(apu->triangle);
	pulse_destroy(apu->pulse[1]);
	pulse_destroy(apu->pulse[0]);
	free(apu);
}