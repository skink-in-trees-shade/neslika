#include <windows.h>
#include <stdlib.h>
#include <mmreg.h>
#include "platform/audio.h"

const long apu_frequency = 1786840; // 1789773;

#define BUF_SIZE 800

struct audio {
	HWAVEOUT hWaveOut;
	uint16_t rate;
	float *samples;
	size_t samples_count;
	float dt;
	float acc;
};

static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
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
	audio->rate = rate;
	audio->dt = (float)apu_frequency / audio->rate;
	audio->samples = calloc(BUF_SIZE, sizeof(float));

	WAVEFORMATEX wfx = { 0 };
	wfx.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
	wfx.wBitsPerSample = 32;
	wfx.nSamplesPerSec = rate;
	wfx.nChannels = channels;
	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	waveOutOpen(&audio->hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_FUNCTION);

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
	LPWAVEHDR lpWaveHdr = calloc(1, sizeof(WAVEHDR));
	lpWaveHdr->dwBufferLength = audio->samples_count * sizeof(float);
	lpWaveHdr->lpData = calloc(1, lpWaveHdr->dwBufferLength);
	memcpy(lpWaveHdr->lpData, audio->samples, lpWaveHdr->dwBufferLength);
	waveOutPrepareHeader(audio->hWaveOut, lpWaveHdr, sizeof(WAVEHDR));
	waveOutWrite(audio->hWaveOut, lpWaveHdr, sizeof(WAVEHDR));
	audio->samples_count = 0;
}

void audio_destroy(struct audio *audio) {
	waveOutReset(audio->hWaveOut);
	waveOutClose(audio->hWaveOut);
	free(audio->samples);
	free(audio);
}