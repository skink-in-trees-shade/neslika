#include <stdlib.h>
#include <SDL2/SDL.h>
#include "platform/audio.h"

const long apu_frequency = 1786840; // 1789773;

#define BUF_SIZE 800

struct audio {
	SDL_AudioDeviceID device;
	uint16_t rate;
	float *samples;
	size_t samples_count;
	float dt;
	float acc;
};

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->dt = apu_frequency / audio->rate;
	audio->samples = calloc(BUF_SIZE, sizeof(float));

	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioSpec spec = {0};
	spec.freq = audio->rate;
	spec.format = AUDIO_F32SYS;
	spec.channels = channels;
	spec.samples = BUF_SIZE;
	audio->device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
	SDL_PauseAudioDevice(audio->device, 0);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	if (audio->samples_count < BUF_SIZE) {
		audio->acc += 1.0;
		if (audio->acc >= audio->dt) {
			audio->samples[audio->samples_count++] = (float)sample;
			audio->acc -= audio->dt;
		}
	}
}

int audio_frame_ready(struct audio *audio) {
	return audio->samples_count == BUF_SIZE;
}

void audio_frame_commit(struct audio *audio) {
	SDL_QueueAudio(audio->device, audio->samples, audio->samples_count * sizeof(float));
	audio->samples_count = 0;
}

void audio_destroy(struct audio *audio) {
	SDL_CloseAudioDevice(audio->device);
	SDL_Quit();
	free(audio->samples);
	free(audio);
}