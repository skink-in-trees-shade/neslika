#include "imm.h"

void imm(struct cpu *cpu) {
	cpu_peek(cpu, cpu->program_counter);
	cpu->operand = cpu->program_counter++;
}