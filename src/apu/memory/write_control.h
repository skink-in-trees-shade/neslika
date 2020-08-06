#ifndef WRITE_CONTROL_H
#define WRITE_CONTROL_H

#include <stdint.h>

void write_control(void *device, uint16_t address, uint8_t value);

#endif