#include "tax.h"

void tax(struct cpu *cpu) {
	cpu->x = cpu->accumulator;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
}