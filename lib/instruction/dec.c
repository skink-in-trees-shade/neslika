#include "dec.h"

void dec(struct cpu *cpu) {
	uint8_t result = cpu->operand - 1;
	cpu->memory[cpu->operand_address] = result;
	cpu_zero(cpu, result);
	cpu_negative(cpu, result);
}