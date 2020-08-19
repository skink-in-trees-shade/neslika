#include "rla.h"

void rla(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu_poke(cpu, cpu->operand, operand);
	uint8_t carry = cpu->carry ? 0x01 : 0x00;
	cpu->carry = operand & 0x80;
	operand <<= 1;
	operand += carry;
	cpu_poke(cpu, cpu->operand, operand);

	cpu->accumulator &= operand;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}