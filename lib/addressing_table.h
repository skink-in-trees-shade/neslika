#ifndef ADDRESSING_TABLE_H
#define ADDRESSING_TABLE_H

#include "cpu.h"

typedef void (*addressing_t)(cpu_t *);

extern addressing_t addressing_table[0x100];

#endif