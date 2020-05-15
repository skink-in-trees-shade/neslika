#include <stdint.h>
#include "bvs.h"

void bvs(struct cpu *cpu) {
	if (cpu->overflow) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}