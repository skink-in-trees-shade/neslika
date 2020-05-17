#include "cmp.h"

void cmp(struct cpu *cpu) {
	uint8_t result = cpu->accumulator - cpu_peek(cpu, cpu->operand);
	cpu->carry = cpu->accumulator >= result;
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
	cpu->extra_execute_cycle = true;
}