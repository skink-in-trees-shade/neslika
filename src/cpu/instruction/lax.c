#include "lax.h"

void lax(struct cpu *cpu) {
	cpu->x = cpu->accumulator = cpu_peek(cpu, cpu->operand);
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
	cpu->extra_execute_cycle = true;
}