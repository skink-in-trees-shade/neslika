#ifndef UXROM_SELECT_BANK_H
#define UXROM_SELECT_BANK_H

#include <stdint.h>

void uxrom_select_bank(void *device, uint16_t address, uint8_t value);

#endif