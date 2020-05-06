#include "bne.h"

void bne(struct cpu *cpu) {
	if (!cpu->zero) {
		cpu->program_counter += cpu->operand;
	}
}