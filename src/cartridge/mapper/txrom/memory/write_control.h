#ifndef TXROM_WRITE_CONTROL_H
#define TXROM_WRITE_CONTROL_H

#include <stdint.h>

void txrom_write_control(void *device, uint16_t address, uint8_t value);

#endif