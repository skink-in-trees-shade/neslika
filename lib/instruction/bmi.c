#include "bmi.h"

void bmi(cpu_t *cpu) {
	if (cpu->negative) {
		cpu->program_counter += cpu->operand;
	}
}