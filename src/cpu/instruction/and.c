#include "and.h"

void and(struct cpu *cpu) {
	cpu->accumulator &= cpu_peek(cpu, cpu->operand);
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
	cpu->extra_execute_cycle = true;
}