#include "imm.h"

void imm(struct cpu *cpu) {
	cpu->operand = cpu->program_counter++;
}