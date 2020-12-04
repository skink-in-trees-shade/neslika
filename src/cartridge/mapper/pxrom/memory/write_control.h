#ifndef PXROM_WRITE_CONTROL_H
#define PXROM_WRITE_CONTROL_H

#include <stdint.h>

void pxrom_write_control(void *device, uint16_t address, uint8_t value);

#endif