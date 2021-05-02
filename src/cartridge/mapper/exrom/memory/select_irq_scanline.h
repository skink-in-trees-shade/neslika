#ifndef EXROM_SELECT_IRQ_SCANLINE_H
#define EXROM_SELECT_IRQ_SCANLINE_H

#include <stdint.h>

void exrom_select_irq_scanline(void *device, uint16_t address, uint8_t value);

#endif