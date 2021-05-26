#include <windows.h>
#include <mmreg.h>
#include <stdlib.h>
#include "blip_buf.h"
#include "platform/audio.h"

struct audio {
	HWAVEOUT hWaveOut;
	blip_buffer_t *buffer;
	unsigned int clock;
	short last_sample;
};

static void CALLBACK callback(HWAVEOUT hWaveOut, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
	(void)dwInstance;
	(void)dwParam2;

	if (uMsg == WOM_DONE) {
		LPWAVEHDR lpWaveHdr = (LPWAVEHDR)dwParam1;
		waveOutUnprepareHeader(hWaveOut, lpWaveHdr, sizeof(WAVEHDR));
		free(lpWaveHdr->lpData);
		free(lpWaveHdr);
	}
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->buffer = blip_new(rate / 10);
	blip_set_rates(audio->buffer, 1786830.0, rate);

	WAVEFORMATEX wfx = {0};
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.wBitsPerSample = 16;
	wfx.nSamplesPerSec = rate;
	wfx.nChannels = channels;
	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	waveOutOpen(&audio->hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)&callback, (DWORD_PTR)audio, CALLBACK_FUNCTION);

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

	LPWAVEHDR lpWaveHdr = calloc(1, sizeof(WAVEHDR));
	lpWaveHdr->lpData = calloc(avail, sizeof(short));
	lpWaveHdr->dwBufferLength = avail * sizeof(short);
	
	blip_read_samples(audio->buffer, (short *)lpWaveHdr->lpData, avail, 0);
	audio->clock = 0;

	waveOutPrepareHeader(audio->hWaveOut, lpWaveHdr, sizeof(WAVEHDR));
	waveOutWrite(audio->hWaveOut, lpWaveHdr, sizeof(WAVEHDR));
}

void audio_destroy(struct audio *audio) {
	//waveOutReset(audio->hWaveOut);
	waveOutClose(audio->hWaveOut);
	blip_delete(audio->buffer);
	free(audio);
}