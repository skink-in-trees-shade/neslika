#include <stdint.h>
#include "bmi.h"

void bmi(struct cpu *cpu) {
	if (cpu->negative) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}