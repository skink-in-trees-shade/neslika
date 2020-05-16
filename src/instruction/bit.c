#include "bit.h"

void bit(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu_zero(cpu, cpu->accumulator & operand);
	cpu_negative(cpu, operand);
	cpu->overflow = operand & 0x40;
}