#include "rra.h"

void rra(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	uint8_t borrow = cpu->carry ? 0x80 : 0x00;
	cpu->carry = operand & 0x01;
	operand >>= 1;
	operand += borrow;
	cpu_poke(cpu, cpu->operand, operand);

	uint16_t result = cpu->accumulator + operand + (cpu->carry ? 0x01 : 0x00);
	cpu->carry = result > 0xFF;
	cpu->overflow = (cpu->accumulator ^ result) & (operand ^ result) & 0x80;
	cpu->accumulator = result & 0xFF;
	cpu_zero(cpu, cpu->accumulator);
	cpu_negative(cpu, cpu->accumulator);
}