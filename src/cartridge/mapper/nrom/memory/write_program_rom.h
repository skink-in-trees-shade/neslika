#ifndef NROM_WRITE_PROGRAM_ROM_H
#define NROM_WRITE_PROGRAM_ROM_H

#include <stdint.h>

void nrom_write_program_rom(void *device, uint16_t address, uint8_t value);

#endif