#include <stdlib.h>
#include <alsa/asoundlib.h>
#include "platform/audio.h"

struct audio {
	snd_pcm_t *handle;
};

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));

	snd_pcm_open(&audio->handle, "default", SND_PCM_STREAM_PLAYBACK, SND_PCM_ASYNC | SND_PCM_NONBLOCK);
	snd_pcm_set_params(audio->handle, SND_PCM_FORMAT_FLOAT64, SND_PCM_ACCESS_RW_INTERLEAVED, channels, rate, 1, 500000);

	return audio;
}

void audio_samples(struct audio *audio, double *samples, size_t count) {
	int error = snd_pcm_writei(audio->handle, samples, count);
	if (error < 0) {
		snd_pcm_recover(audio->handle, error, 0);
	}
}

void audio_destroy(struct audio *audio) {
	snd_pcm_drain(audio->handle);
	snd_pcm_close(audio->handle);
	free(audio);
}