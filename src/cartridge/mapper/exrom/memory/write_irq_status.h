#ifndef EXROM_WRITE_IRQ_STATUS_H
#define EXROM_WRITE_IRQ_STATUS_H

#include <stdint.h>

void exrom_write_irq_status(void *device, uint16_t address, uint8_t value);

#endif