#include "sre.h"

void sre(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu->carry = operand & 0x01;
	operand >>= 1;
	cpu_poke(cpu, cpu->operand, operand);

	cpu->accumulator ^= operand;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}