#include <windows.h>
#include <mmreg.h>
#include <stdlib.h>
#include "platform/audio.h"

struct audio {
	HWAVEOUT hWaveOut;
};

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));

	WAVEFORMATEX wfx = {0};
	wfx.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
	wfx.wBitsPerSample = 32;
	wfx.nSamplesPerSec = rate;
	wfx.nChannels = channels;
	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	waveOutOpen(&audio->hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	return audio;
}

void audio_samples(struct audio *audio, double *samples, size_t count) {
	float *conv = calloc(count, sizeof(float));
	for (size_t i = 0; i < count; i++) {
		conv[i] = (float)samples[i];
	}

	WAVEHDR waveHdr = {0};
	waveHdr.lpData = (LPSTR)conv;
	waveHdr.dwBufferLength = count * sizeof(float);
	waveOutPrepareHeader(audio->hWaveOut, &waveHdr, sizeof(WAVEHDR));

	waveOutWrite(audio->hWaveOut, &waveHdr, sizeof(WAVEHDR));

	free(conv);
}

void audio_destroy(struct audio *audio) {
	waveOutReset(audio->hWaveOut);
	waveOutClose(audio->hWaveOut);
	free(audio);
}