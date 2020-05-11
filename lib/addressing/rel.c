#include "rel.h"

void rel(struct cpu *cpu) {
	cpu->operand_address = cpu->program_counter++;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
	cpu->addressing_mode = addressing_relative;
}