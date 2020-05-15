#ifndef ADDRESSING_TABLE_H
#define ADDRESSING_TABLE_H

#include "cpu.h"

typedef void (*addressing_fn)(struct cpu *);

extern addressing_fn addressing_table[0x100];

#endif