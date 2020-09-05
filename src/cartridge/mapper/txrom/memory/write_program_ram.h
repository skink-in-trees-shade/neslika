#ifndef TXROM_WRITE_PROGRAM_RAM_H
#define TXROM_WRITE_PROGRAM_RAM_H

#include <stdint.h>

void txrom_write_program_ram(void *device, uint16_t address, uint8_t value);

#endif