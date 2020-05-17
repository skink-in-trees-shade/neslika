#include <stdint.h>
#include "bmi.h"

void bmi(struct cpu *cpu) {
	if (cpu->negative) {
		cpu->cycle++;

		uint16_t result = cpu->program_counter + (int8_t)cpu->operand;
		if ((result & 0xFF00) != (cpu->program_counter & 0xFF00)) {
			cpu->cycle++;
		}

		cpu->program_counter = result;
	}
}