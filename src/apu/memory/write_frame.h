#ifndef WRITE_FRAME_H
#define WRITE_FRAME_H

#include <stdint.h>

void write_frame(void *device, uint16_t address, uint8_t value);

#endif