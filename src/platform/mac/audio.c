#include <AudioUnit/AudioUnit.h>
#include <stdlib.h>
#include "platform/audio.h"

const long apu_frequency = 1789773;

struct audio {
	AudioUnit unit;
	uint16_t rate;
	float *samples;
	size_t samples_size;
	size_t read_position;
	size_t write_position;
	unsigned long cycle;
};

static OSStatus callback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData) {
	(void)ioActionFlags;
	(void)inTimeStamp;
	(void)inBusNumber;

	struct audio *audio = inRefCon;
	memcpy(ioData->mBuffers[0].mData, &audio->samples[audio->read_position], inNumberFrames * sizeof(float));
	audio->read_position = (audio->read_position + inNumberFrames) % audio->samples_size;
	return noErr;
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->rate = rate;
	audio->samples_size = audio->rate;
	audio->samples = calloc(audio->samples_size, sizeof(float));

	AudioComponentDescription component_description = {
		.componentType = kAudioUnitType_Output,
		.componentSubType = kAudioUnitSubType_DefaultOutput,
		.componentManufacturer = kAudioUnitManufacturer_Apple,
	};
	AudioComponent component = AudioComponentFindNext(NULL, &component_description);
	AudioComponentInstanceNew(component, &audio->unit);

	AURenderCallbackStruct callback_description = { .inputProc = callback, .inputProcRefCon = audio };
	AudioUnitSetProperty(audio->unit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &callback_description, sizeof(callback_description));

	AudioStreamBasicDescription stream_description = {
		.mFormatID = kAudioFormatLinearPCM,
		.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsNonInterleaved,
		.mSampleRate = rate,
		.mBitsPerChannel = 8 * sizeof(float),
		.mChannelsPerFrame = channels,
		.mFramesPerPacket = 1,
		.mBytesPerFrame = sizeof(float),
		.mBytesPerPacket = sizeof(float),
	};
	AudioUnitSetProperty(audio->unit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &stream_description, sizeof(stream_description));

	AudioUnitInitialize(audio->unit);
	AudioOutputUnitStart(audio->unit);

	return audio;
}

void audio_sample(struct audio *audio, double sample) {
	if (audio->cycle % (apu_frequency / audio->rate) == 0) {
		audio->samples[audio->write_position] = sample;
		audio->write_position = (audio->write_position + 1) % audio->samples_size;
	}

	audio->cycle++;
}

void audio_destroy(struct audio *audio) {
	AudioOutputUnitStop(audio->unit);
	AudioUnitUninitialize(audio->unit);
	AudioComponentInstanceDispose(audio->unit);
	free(audio);
}