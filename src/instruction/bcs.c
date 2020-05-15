#include <stdint.h>
#include "bcs.h"

void bcs(struct cpu *cpu) {
	if (cpu->carry) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}