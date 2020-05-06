#include "sty.h"

void sty(struct cpu *cpu) {
	cpu->memory[cpu->operand_address] = cpu->y;
}