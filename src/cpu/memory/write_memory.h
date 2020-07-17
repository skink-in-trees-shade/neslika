#ifndef WRITE_MEMORY_H
#define WRITE_MEMORY_H

#include <stdint.h>

void write_memory(void *device, uint16_t address, uint8_t value);

#endif