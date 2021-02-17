#include <stdlib.h>
#include <alsa/asoundlib.h>
#include "platform/audio.h"

const long apu_frequency = 1786840;

struct audio {
	snd_pcm_t *handle;
	uint16_t rate;
	double *samples;
	size_t samples_count;
	size_t samples_size;
	float dt;
	float acc;
};

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->dt = apu_frequency / audio->rate;
	audio->samples_size = audio->rate / 60;
	audio->samples = calloc(audio->samples_size, sizeof(double));

	snd_pcm_open(&audio->handle, "default", SND_PCM_STREAM_PLAYBACK, SND_PCM_ASYNC | SND_PCM_NONBLOCK);
	snd_pcm_set_params(audio->handle, SND_PCM_FORMAT_FLOAT64, SND_PCM_ACCESS_RW_INTERLEAVED, channels, rate, 1, 500000);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	if (audio->samples_count < audio->samples_size) {
		audio->acc += 1.0;
		if (audio->acc >= audio->dt) {
			audio->samples[audio->samples_count++] = sample;
			audio->acc -= audio->dt;
		}
	}
}

int audio_frame_ready(struct audio *audio) {
	return audio->samples_count == audio->samples_size;
}

void audio_frame_commit(struct audio *audio) {
	int error = snd_pcm_writei(audio->handle, audio->samples, audio->samples_size);
	if (error < 0) {
		snd_pcm_recover(audio->handle, error, 0);
	}
	audio->samples_count = 0;
}

void audio_destroy(struct audio *audio) {
	snd_pcm_drain(audio->handle);
	snd_pcm_close(audio->handle);
	free(audio->samples);
	free(audio);
}