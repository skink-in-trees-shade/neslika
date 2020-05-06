#include "bpl.h"

void bpl(struct cpu *cpu) {
	if (!cpu->negative) {
		cpu->program_counter += cpu->operand;
	}
}