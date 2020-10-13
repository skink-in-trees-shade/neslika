#include <SDL.h>
#include <stdlib.h>
#include "buffer.h"
#include "audio.h"

const long apu_frequency = 1789773;

struct audio {
	SDL_AudioDeviceID dev;
	struct buffer *buffer;
	uint16_t rate;
	unsigned long cycle;
};

static void callback(void *userdata, Uint8 *stream, int length) {
	struct audio *audio = userdata;

	size_t available = buffer_available(audio->buffer);
	size_t required = length / sizeof(float);
	if (available >= required) {
		buffer_read(audio->buffer, (float *)stream, required);
	}
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->buffer = buffer_new(rate);

	SDL_InitSubSystem(SDL_INIT_AUDIO);

	SDL_AudioSpec spec = {0};
	spec.freq = rate;
	spec.format = AUDIO_F32SYS;
	spec.channels = channels;
	spec.samples = 1024;
	spec.callback = callback;
	spec.userdata = audio;

	audio->dev = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
	SDL_PauseAudioDevice(audio->dev, 0);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	if (audio->cycle % (apu_frequency / audio->rate) == 0) {
		SDL_LockAudioDevice(audio->dev);
		float pls = sample * 5;
		buffer_write(audio->buffer, &pls, 1);
		SDL_UnlockAudioDevice(audio->dev);
	}

	audio->cycle++;
}

void audio_destroy(struct audio *audio) {
	SDL_CloseAudioDevice(audio->dev);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	buffer_destroy(audio->buffer);
	free(audio);
}