#include <stdlib.h>
#include <SDL2/SDL.h>
#include "platform/audio.h"

const long apu_frequency = 1786840; // 1789773

#define BUF_SIZE 256*16*2

struct audio {
	SDL_AudioDeviceID device;
	uint16_t rate;
	float *samples;
	size_t samples_count;
	float dt;
	float acc;
	int started;
};

#include <stdio.h>
static void callback(void *userdata, Uint8 *stream, int len) {
	struct audio *audio = userdata;

	size_t samples_count = len / sizeof(float);
	printf("HAVE %4ld  WANT %4ld", audio->samples_count, samples_count);
	if (samples_count <= audio->samples_count) {
		memcpy(stream, audio->samples, samples_count * sizeof(float));
		memmove(audio->samples, &audio->samples[samples_count], (audio->samples_count - samples_count) * sizeof(float));
		audio->samples_count -= samples_count;
		printf("  LEFT %4ld\n", audio->samples_count);
	} else {
		memcpy(stream, audio->samples, audio->samples_count * sizeof(float));
		memset(&stream[audio->samples_count], 0, (samples_count - audio->samples_count) * sizeof(float));
		printf("  MUTE %4ld\n", samples_count - audio->samples_count);
		audio->samples_count = 0;
	}
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->dt = apu_frequency / audio->rate;
	audio->samples = calloc(BUF_SIZE * 32, sizeof(float));

	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioSpec spec = {0};
	spec.freq = audio->rate;
	spec.format = AUDIO_F32SYS;
	spec.channels = channels;
	spec.samples = BUF_SIZE;
	spec.callback = &callback;
	spec.userdata = audio;
	audio->device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	audio->acc += 1.0;
	if (audio->acc >= audio->dt) {
		audio->samples[audio->samples_count++] = (float)sample;
		audio->acc -= audio->dt;
		if (!audio->started && audio->samples_count == BUF_SIZE) {
			audio->started = 1;
			SDL_PauseAudioDevice(audio->device, 0);
		}
	}
}

void audio_destroy(struct audio *audio) {
	SDL_CloseAudioDevice(audio->device);
	SDL_Quit();
	free(audio->samples);
	free(audio);
}