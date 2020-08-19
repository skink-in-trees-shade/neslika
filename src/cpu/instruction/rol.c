#include "rol.h"

void rol(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu_poke(cpu, cpu->operand, operand);
	uint8_t carry = cpu->carry ? 0x01 : 0x00;
	cpu->carry = operand & 0x80;
	operand <<= 1;
	operand += carry;
	cpu_zero(cpu, operand);
	cpu_negative(cpu, operand);
	cpu_poke(cpu, cpu->operand, operand);
}