#ifndef ADDRESSING_TABLE_H
#define ADDRESSING_TABLE_H

#include <stdint.h>
#include "cpu.h"

typedef uint16_t (*addressing_t)(cpu_t *);

extern addressing_t addressing_table[0x100];

#endif