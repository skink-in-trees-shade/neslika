#include "bvs.h"

void bvs(struct cpu *cpu) {
	if (cpu->overflow) {
		cpu->program_counter += cpu->operand;
	}
}