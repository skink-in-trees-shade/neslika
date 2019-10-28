#include "sta.h"

void sta(cpu_t *cpu) {
	cpu->memory[cpu->operand_address] = cpu->accumulator;
}