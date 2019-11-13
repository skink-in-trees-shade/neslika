#include "jmp.h"

void jmp(cpu_t *cpu) {
	cpu->program_counter = cpu->operand;
}