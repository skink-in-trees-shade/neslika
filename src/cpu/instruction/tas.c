#include "tas.h"

void tas(struct cpu *cpu) {
	cpu->stack_pointer = cpu->accumulator & cpu->x;

	uint8_t operand_high = cpu->operand >> 8;
	cpu_poke(cpu, cpu->operand, cpu->stack_pointer & operand_high);
}