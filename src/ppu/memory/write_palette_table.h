#ifndef WRITE_PALETTE_TABLE_H
#define WRITE_PALETTE_TABLE_H

#include <stdint.h>

void write_palette_table(void *device, uint16_t address, uint8_t value);

#endif