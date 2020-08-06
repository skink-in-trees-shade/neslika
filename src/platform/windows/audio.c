#include <windows.h>
#include <mmreg.h>
#include <stdlib.h>
#include "platform/audio.h"

const long apu_frequency = 1789773;

#define NBUF 4

struct audio {
	HWAVEOUT hWaveOut;
	uint16_t rate;
	HANDLE thread;
	HANDLE mutex;
	float *samples[NBUF];
	size_t samples_size;
	BOOL samples_full[NBUF];
	size_t write_position;
	size_t current_buffer;
	unsigned long cycle;
};

static DWORD callback(LPVOID param) {
	struct audio *audio = param;

	long buffer_id = 0;
	while (1) {
		if (audio->samples_full[buffer_id]) {
			WaitForSingleObject(audio->mutex, INFINITE);

			WAVEHDR waveHdr = {0};
			waveHdr.lpData = (LPSTR)audio->samples[buffer_id];
			waveHdr.dwBufferLength = audio->samples_size * sizeof(float);
			waveOutPrepareHeader(audio->hWaveOut, &waveHdr, sizeof(WAVEHDR));

			waveOutWrite(audio->hWaveOut, &waveHdr, sizeof(WAVEHDR));

			audio->samples_full[buffer_id] = FALSE;
			buffer_id = (buffer_id + 1) % NBUF;

			ReleaseMutex(audio->mutex);
		}
		Sleep(1);
	}

	return 0;
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->samples_size = audio->rate;
	for (size_t i = 0; i < NBUF; i++) {
		audio->samples[i] = calloc(audio->samples_size, sizeof(float));
	}

	WAVEFORMATEX wfx = {0};
	wfx.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
	wfx.wBitsPerSample = 32;
	wfx.nSamplesPerSec = rate;
	wfx.nChannels = channels;
	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
	waveOutOpen(&audio->hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);

	timeBeginPeriod(1);

	audio->thread = CreateThread(NULL, 0, callback, audio, 0, NULL);
	audio->mutex = CreateMutex(NULL, FALSE, NULL);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	if (audio->cycle % (apu_frequency / audio->rate) == 0) {
		WaitForSingleObject(audio->mutex, INFINITE);
		audio->samples[audio->current_buffer][audio->write_position++] = sample;
		if (audio->write_position == audio->samples_size) {
			audio->samples_full[audio->current_buffer] = TRUE;
			audio->current_buffer = (audio->current_buffer + 1) % NBUF;
			audio->write_position = 0;
		}
		ReleaseMutex(audio->mutex);
	}

	audio->cycle++;
}

void audio_destroy(struct audio *audio) {
	CloseHandle(audio->mutex);
	CloseHandle(audio->thread);
	timeEndPeriod(1);
	waveOutReset(audio->hWaveOut);
	waveOutClose(audio->hWaveOut);
	for (size_t i = 0; i < NBUF; i++) {
		free(audio->samples[i]);
	}
	free(audio);
}