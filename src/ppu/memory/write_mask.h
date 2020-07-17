#ifndef WRITE_MASK_H
#define WRITE_MASK_H

#include <stdint.h>

void write_mask(void *device, uint16_t address, uint8_t value);

#endif