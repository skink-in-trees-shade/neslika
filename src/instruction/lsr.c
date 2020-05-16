#include "lsr.h"

void lsr(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu->carry = operand & 0x01;
	operand >>= 1;
	cpu_zero(cpu, operand);
	cpu_negative(cpu, operand);
	cpu_poke(cpu, cpu->operand, operand);
}