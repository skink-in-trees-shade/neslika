#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <stddef.h>

struct audio;

struct audio *audio_new(uint8_t channels, uint16_t rate);
void audio_samples(struct audio *audio, double *samples, size_t count);
void audio_destroy(struct audio *audio);

#endif