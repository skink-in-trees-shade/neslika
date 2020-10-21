#include <SDL.h>
#include <stdlib.h>
#include "audio.h"

struct audio {
	SDL_AudioDeviceID device;
	SDL_AudioStream *stream;
};

static void callback(void *userdata, Uint8* stream, int length) {
	struct audio *audio = userdata;
	SDL_AudioStreamGet(audio->stream, stream, length);
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));

	SDL_InitSubSystem(SDL_INIT_AUDIO);

	SDL_AudioSpec actual;
	SDL_AudioSpec desired = {0};
	desired.freq = rate;
	desired.format = AUDIO_U8;
	desired.channels = channels;
	desired.callback = callback;
	desired.userdata = audio;

	audio->device = SDL_OpenAudioDevice(NULL, 0, &desired, &actual, 0);
	audio->stream = SDL_NewAudioStream(desired.format, desired.channels, 1792114, actual.format, actual.channels, actual.freq);
	SDL_PauseAudioDevice(audio->device, 0);

	return audio;
}

void audio_sample(struct audio *audio, uint8_t sample) {
	SDL_AudioStreamPut(audio->stream, &sample, sizeof(uint8_t));
}

void audio_destroy(struct audio *audio) {
	SDL_FreeAudioStream(audio->stream);
	SDL_CloseAudioDevice(audio->device);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	free(audio);
}