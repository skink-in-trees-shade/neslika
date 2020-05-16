#include "inc.h"

void inc(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	operand++;
	cpu_poke(cpu, cpu->operand, operand);
	cpu_zero(cpu, operand);
	cpu_negative(cpu, operand);
}