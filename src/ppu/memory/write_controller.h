#ifndef WRITE_CONTROLLER_H
#define WRITE_CONTROLLER_H

#include <stdint.h>

void write_controller(void *device, uint16_t address, uint8_t value);

#endif