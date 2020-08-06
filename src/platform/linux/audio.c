#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <pthread.h>
#include "platform/audio.h"

const long apu_frequency = 1789773;

struct audio {
	snd_pcm_t *handle;
	uint16_t rate;
	pthread_t thread;
	pthread_mutex_t mutex;
	double *samples;
	size_t samples_size;
	size_t read_position;
	size_t write_position;
	unsigned long cycle;
};

static void *callback(void *arg) {
	struct audio *audio = arg;

	while (1) {
		if (snd_pcm_wait(audio->handle, 1000) == 1) {
			snd_pcm_sframes_t frames = snd_pcm_avail_update(audio->handle);
			if (frames > 0) {
				pthread_mutex_lock(&audio->mutex);
				int error = snd_pcm_writei(audio->handle, &audio->samples[audio->read_position], frames);
				pthread_mutex_unlock(&audio->mutex);

				if (error < 0) {
					snd_pcm_recover(audio->handle, error, 0);
				} else {
					audio->read_position = (audio->read_position + error) % audio->samples_size;
				}
			}
		}
	}

	return NULL;
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->samples_size = audio->rate;
	audio->samples = calloc(audio->samples_size, sizeof(double));

	snd_pcm_open(&audio->handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	snd_pcm_set_params(audio->handle, SND_PCM_FORMAT_FLOAT64, SND_PCM_ACCESS_RW_INTERLEAVED, channels, rate, 1, 100000);

	pthread_create(&audio->thread, NULL, callback, (void *)audio);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	if (audio->cycle % (apu_frequency / audio->rate) == 0) {
		pthread_mutex_lock(&audio->mutex);
		audio->samples[audio->write_position] = sample;
		pthread_mutex_unlock(&audio->mutex);

		audio->write_position = (audio->write_position + 1) % audio->samples_size;
	}

	audio->cycle++;
}

void audio_destroy(struct audio *audio) {
	pthread_cancel(audio->thread);
	snd_pcm_drain(audio->handle);
	snd_pcm_close(audio->handle);
	free(audio->samples);
	free(audio);
}