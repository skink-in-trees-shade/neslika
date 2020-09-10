#include "imp.h"

void imp(struct cpu *cpu) {
	cpu->operand = 0x0000;
	cpu_peek(cpu, cpu->program_counter);
}