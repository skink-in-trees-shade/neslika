#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

typedef void (*instruction_t)(cpu_t *);

extern instruction_t instructions[0x100];

#endif