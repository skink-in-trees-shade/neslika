#ifndef WRITE_OAM_ADDRESS_H
#define WRITE_OAM_ADDRESS_H

#include <stdint.h>

void write_oam_address(void *device, uint16_t address, uint8_t value);

#endif