#ifndef UTIL_H
#define UTIL_H

#include "cpu.h"

void cpu_compare(struct cpu *left, struct cpu *right);
struct cpu *cpu_random(void);
struct cpu *cpu_clone(struct cpu *cpu);

#endif