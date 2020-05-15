#include "imm.h"

void imm(struct cpu *cpu) {
	cpu->operand_address = cpu->program_counter++;
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
}