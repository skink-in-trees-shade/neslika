#ifndef EXROM_WRITE_MIRRORING_H
#define EXROM_WRITE_MIRRORING_H

#include <stdint.h>

void exrom_write_mirroring(void *device, uint16_t address, uint8_t value);

#endif