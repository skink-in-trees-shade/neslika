#include <stdint.h>
#include "bvc.h"

void bvc(struct cpu *cpu) {
	if (!cpu->overflow) {
		cpu->cycle++;

		uint16_t result = cpu->program_counter + (int8_t)cpu->operand;
		if ((result & 0xFF00) != (cpu->program_counter & 0xFF00)) {
			cpu->cycle++;
		}

		cpu->program_counter = result;
	}
}