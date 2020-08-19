#include "asl.h"

void asl(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu_poke(cpu, cpu->operand, operand);
	cpu->carry = operand & 0x80;
	operand <<= 1;
	cpu_zero(cpu, operand);
	cpu_negative(cpu, operand);
	cpu_poke(cpu, cpu->operand, operand);
}