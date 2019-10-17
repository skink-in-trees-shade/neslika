#ifndef UTIL_H
#define UTIL_H

#include "cpu.h"

void cpu_compare(cpu_t *left, cpu_t *right);
cpu_t *cpu_random(void);
cpu_t *cpu_clone(cpu_t *cpu);

#endif