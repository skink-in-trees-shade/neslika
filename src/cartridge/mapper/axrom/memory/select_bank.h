#ifndef AXROM_SELECT_BANK_H
#define AXROM_SELECT_BANK_H

#include <stdint.h>

void axrom_select_bank(void *device, uint16_t address, uint8_t value);

#endif