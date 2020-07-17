#ifndef WRITE_OAM_DMA_H
#define WRITE_OAM_DMA_H

#include <stdint.h>

void write_oam_dma(void *device, uint16_t address, uint8_t value);

#endif