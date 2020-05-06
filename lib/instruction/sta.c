#include "sta.h"

void sta(struct cpu *cpu) {
	cpu->memory[cpu->operand_address] = cpu->accumulator;
}