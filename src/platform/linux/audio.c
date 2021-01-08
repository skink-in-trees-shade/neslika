#include <stdlib.h>
#include <alsa/asoundlib.h>
#include "platform/audio.h"

const long apu_frequency = 1789773;

struct audio {
	snd_pcm_t *handle;
	uint16_t rate;
	double *samples;
	size_t samples_count;
};

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->samples = calloc(apu_frequency * 5, sizeof(double));

	snd_pcm_open(&audio->handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	snd_pcm_set_params(audio->handle, SND_PCM_FORMAT_FLOAT64, SND_PCM_ACCESS_RW_INTERLEAVED, channels, rate, 1, 100000);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	audio->samples[audio->samples_count++] = sample;
}

void audio_update(struct audio *audio) {
	size_t size = audio->rate / 60;

	double *samples = calloc(size, sizeof(double));
	for (size_t i = 0; i < size; i++) {
		samples[i] = audio->samples[i * (size_t)(audio->samples_count / size)];
	}
	audio->samples_count = 0;

	int error = snd_pcm_writei(audio->handle, samples, size);
	if (error < 0) {
		snd_pcm_recover(audio->handle, error, 0);
	}
}

void audio_destroy(struct audio *audio) {
	snd_pcm_drain(audio->handle);
	snd_pcm_close(audio->handle);
	free(audio->samples);
	free(audio);
}