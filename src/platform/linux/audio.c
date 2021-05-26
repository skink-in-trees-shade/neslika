#include <alsa/asoundlib.h>
#include <stdlib.h>
#include "blip_buf.h"
#include "platform/audio.h"

struct audio {
	snd_pcm_t *handle;
	blip_buffer_t *buffer;
	unsigned int clock;
	short last_sample;
};

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->buffer = blip_new(rate / 10);
	blip_set_rates(audio->buffer, 1786830.0, rate);

	snd_pcm_open(&audio->handle, "default", SND_PCM_STREAM_PLAYBACK, SND_PCM_NONBLOCK);
	snd_pcm_set_params(audio->handle, SND_PCM_FORMAT_S16, SND_PCM_ACCESS_RW_INTERLEAVED, channels, rate, 1, 500000);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	short ssample = sample * 32767;
	if (ssample != audio->last_sample) {
		blip_add_delta(audio->buffer, audio->clock, audio->last_sample - ssample);
		audio->last_sample = ssample;
	}
	audio->clock++;
}

void audio_update(struct audio *audio) {
	blip_end_frame(audio->buffer, audio->clock);
	int avail = blip_samples_avail(audio->buffer);

	short *buffer = calloc(avail, sizeof(short));
	blip_read_samples(audio->buffer, buffer, avail, 0);
	audio->clock = 0;

	int error = snd_pcm_writei(audio->handle, buffer, avail);
	if (error < 0) {
		snd_pcm_recover(audio->handle, error, 0);
	}

	free(buffer);
}

void audio_destroy(struct audio *audio) {
	snd_pcm_drain(audio->handle);
	snd_pcm_close(audio->handle);
	blip_delete(audio->buffer);
	free(audio);
}