#include "stx.h"

void stx(struct cpu *cpu) {
	cpu->memory[cpu->operand_address] = cpu->x;
}