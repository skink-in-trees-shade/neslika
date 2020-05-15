#ifndef INSTRUCTION_TABLE_H
#define INSTRUCTION_TABLE_H

#include "cpu.h"

typedef void (*instruction_fn)(struct cpu *);

extern instruction_fn instruction_table[0x100];

#endif