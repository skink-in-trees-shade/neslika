#ifndef TXROM_WRITE_IRQ_COUNTER_H
#define TXROM_WRITE_IRQ_COUNTER_H

#include <stdint.h>

void txrom_write_irq_counter(void *device, uint16_t address, uint8_t value);

#endif