#include <stdlib.h>
#include <alsa/asoundlib.h>
#include "platform/audio.h"

struct audio {
	snd_pcm_t *handle;
	uint16_t rate;
	double *samples;
	size_t samples_count;
};

#define BUF_SIZE 800

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->samples = calloc(BUF_SIZE * 10, sizeof(double));

	snd_pcm_open(&audio->handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	snd_pcm_set_params(audio->handle, SND_PCM_FORMAT_FLOAT64, SND_PCM_ACCESS_RW_INTERLEAVED, channels, rate, 1, 0);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	double dt = 29780 * 60.0 / audio->rate;
	static double acc;
	acc += 1.0;
	if (acc >= dt) {
		audio->samples[audio->samples_count++] = sample;
		acc -= dt;
	}
}

void audio_update(struct audio *audio) {
	int error = snd_pcm_writei(audio->handle, audio->samples, BUF_SIZE);
	if (error < 0) {
		snd_pcm_recover(audio->handle, error, 0);
	}

	audio->samples_count -= BUF_SIZE;
	memmove(audio->samples, &audio->samples[BUF_SIZE], BUF_SIZE * 9 * sizeof(double));
}

int audio_frame_ended(struct audio *audio) {
	return audio->samples_count >= BUF_SIZE;
}

void audio_destroy(struct audio *audio) {
	snd_pcm_drain(audio->handle);
	snd_pcm_close(audio->handle);
	free(audio->samples);
	free(audio);
}