#include "bmi.h"

void bmi(struct cpu *cpu) {
	if (cpu->negative) {
		cpu->program_counter += cpu->operand;
	}
}