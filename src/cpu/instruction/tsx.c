#include "tsx.h"

void tsx(struct cpu *cpu) {
	cpu->x = cpu->stack_pointer;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
}