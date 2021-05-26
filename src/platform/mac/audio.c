#include <AudioUnit/AudioUnit.h>
#include <stdlib.h>
#include "blip_buf.h"
#include "platform/audio.h"

struct audio {
	AudioUnit unit;
	blip_buffer_t *buffer;
	unsigned int clock;
	short last_sample;
};

static OSStatus callback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData) {
	(void)ioActionFlags;
	(void)inTimeStamp;
	(void)inBusNumber;

	struct audio *audio = inRefCon;

	blip_end_frame(audio->buffer, audio->clock);
	int avail = blip_samples_avail(audio->buffer);

	if ((UInt32)avail < inNumberFrames) {
		memset(ioData->mBuffers[0].mData, 0, inNumberFrames * sizeof(short));
		*ioActionFlags |= kAudioUnitRenderAction_OutputIsSilence;
		return noErr;
	}

	blip_read_samples(audio->buffer, ioData->mBuffers[0].mData, inNumberFrames, 0);
	audio->clock = 0;
	return noErr;
}

struct audio *audio_new(uint8_t channels, uint16_t rate) {
	struct audio *audio = calloc(1, sizeof(struct audio));
	audio->buffer = blip_new(rate / 10);
	blip_set_rates(audio->buffer, 1786830.0, rate);

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
		.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsNonInterleaved,
		.mSampleRate = rate,
		.mBitsPerChannel = 8 * sizeof(short),
		.mChannelsPerFrame = channels,
		.mFramesPerPacket = 1,
		.mBytesPerFrame = sizeof(short),
		.mBytesPerPacket = sizeof(short),
	};
	AudioUnitSetProperty(audio->unit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &stream_description, sizeof(stream_description));

	AudioUnitInitialize(audio->unit);
	AudioOutputUnitStart(audio->unit);

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
	(void)audio;
}

void audio_destroy(struct audio *audio) {
	AudioOutputUnitStop(audio->unit);
	AudioUnitUninitialize(audio->unit);
	AudioComponentInstanceDispose(audio->unit);
	blip_delete(audio->buffer);
	free(audio);
}