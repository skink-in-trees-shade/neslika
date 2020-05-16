#include "cpy.h"

void cpy(struct cpu *cpu) {
	uint8_t result = cpu->y - cpu_peek(cpu, cpu->operand);
	cpu->carry = cpu->y >= result;
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}