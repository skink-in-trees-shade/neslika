#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

struct audio;

struct audio *audio_new(uint8_t channels, uint16_t rate);
void audio_sample(struct audio *audio, double sample);
void audio_destroy(struct audio *audio);

#endif