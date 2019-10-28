#include "stx.h"

void stx(cpu_t *cpu) {
	cpu->memory[cpu->operand_address] = cpu->x;
}