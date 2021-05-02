#ifndef EXROM_READ_IRQ_STATUS_H
#define EXROM_READ_IRQ_STATUS_H

#include <stdint.h>

uint8_t exrom_read_irq_status(void *device, uint16_t address);

#endif