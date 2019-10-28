#include "sty.h"

void sty(cpu_t *cpu) {
	cpu->memory[cpu->operand_address] = cpu->y;
}