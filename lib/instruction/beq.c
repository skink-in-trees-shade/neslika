#include "beq.h"

void beq(struct cpu *cpu) {
	if (cpu->zero) {
		cpu->program_counter += cpu->operand;
	}
}