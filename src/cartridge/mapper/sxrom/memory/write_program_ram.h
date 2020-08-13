#ifndef SXROM_WRITE_PROGRAM_RAM_H
#define SXROM_WRITE_PROGRAM_RAM_H

#include <stdint.h>

void sxrom_write_program_ram(void *device, uint16_t address, uint8_t value);

#endif