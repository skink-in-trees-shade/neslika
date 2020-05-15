#include "jmp.h"

void jmp(struct cpu *cpu) {
	cpu->program_counter = cpu->operand;
}