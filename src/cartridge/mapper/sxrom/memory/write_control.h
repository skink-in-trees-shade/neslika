#ifndef SXROM_WRITE_CONTROL_H
#define SXROM_WRITE_CONTROL_H

#include <stdint.h>

void sxrom_write_control(void *device, uint16_t address, uint8_t value);

#endif