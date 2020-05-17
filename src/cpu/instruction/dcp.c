#include "dcp.h"

void dcp(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	operand--;
	cpu_poke(cpu, cpu->operand, operand);

	uint8_t result = cpu->accumulator - operand;
	cpu->carry = cpu->accumulator >= result;
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}