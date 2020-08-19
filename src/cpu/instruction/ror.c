#include "ror.h"

void ror(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu_poke(cpu, cpu->operand, operand);
	uint8_t borrow = cpu->carry ? 0x80 : 0x00;
	cpu->carry = operand & 0x01;
	operand >>= 1;
	operand += borrow;
	cpu_zero(cpu, operand);
	cpu_negative(cpu, operand);
	cpu_poke(cpu, cpu->operand, operand);
}