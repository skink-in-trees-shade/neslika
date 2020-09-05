#ifndef TXROM_SELECT_BANK_H
#define TXROM_SELECT_BANK_H

#include <stdint.h>

void txrom_select_bank(void *device, uint16_t address, uint8_t value);

#endif