#ifndef INSTRUCTION_TABLE_H
#define INSTRUCTION_TABLE_H

#include "cpu.h"

typedef void (*instruction_t)(cpu_t *, uint8_t);

extern instruction_t instruction_table[0x100];

#endif