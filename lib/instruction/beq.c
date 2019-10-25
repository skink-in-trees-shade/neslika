#include "beq.h"

void beq(cpu_t *cpu) {
	if (cpu->zero) {
		cpu->program_counter += cpu->operand;
	}
}