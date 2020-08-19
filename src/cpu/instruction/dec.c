#include "dec.h"

void dec(struct cpu *cpu) {
	uint8_t operand = cpu_peek(cpu, cpu->operand);
	cpu_poke(cpu, cpu->operand, operand);
	operand--;
	cpu_zero(cpu, operand);
	cpu_negative(cpu, operand);
	cpu_poke(cpu, cpu->operand, operand);
}