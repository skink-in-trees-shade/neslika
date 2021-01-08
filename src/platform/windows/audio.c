#include <windows.h>
#include <mmreg.h>
#include <stdlib.h>
#include "platform/audio.h"

const long apu_frequency = 1789773;

struct audio {
	HWAVEOUT hWaveOut;
	uint16_t rate;
	float *samples;
	size_t samples_count;
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
	audio->samples = calloc(apu_frequency * 5, sizeof(float));
	audio->rate = rate;

	WAVEFORMATEX wfx = {0};
	wfx.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
	wfx.wBitsPerSample = 32;
	wfx.nSamplesPerSec = rate;
	wfx.nChannels = channels;
	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	waveOutOpen(&audio->hWaveOut, WAVE_MAPPER | WAVE_FORMAT_DIRECT, &wfx, (DWORD_PTR)&waveOutProc, 0, CALLBACK_FUNCTION);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	audio->samples[audio->samples_count++] = sample;
}

void audio_update(struct audio *audio) {
	static int counter = 0;
	if (counter == 10) {
		size_t size = audio->rate / 6;

		float *samples = calloc(size, sizeof(float));
		for (size_t i = 0; i < size; i++) {
			samples[i] = audio->samples[i * (size_t)(audio->samples_count / size)];
		}
		audio->samples_count = 0;

		LPWAVEHDR lpWaveHdr = calloc(1, sizeof(WAVEHDR));
		lpWaveHdr->lpData = (LPSTR)samples;
		lpWaveHdr->dwBufferLength = size * sizeof(float);

		waveOutPrepareHeader(audio->hWaveOut, lpWaveHdr, sizeof(WAVEHDR));
		waveOutWrite(audio->hWaveOut, lpWaveHdr, sizeof(WAVEHDR));

		counter = 0;
	}
	counter++;
}

void audio_destroy(struct audio *audio) {
	//waveOutReset(audio->hWaveOut);
	waveOutClose(audio->hWaveOut);
	free(audio->samples);
	free(audio);
}