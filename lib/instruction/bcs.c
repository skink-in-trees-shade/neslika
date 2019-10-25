#include "bcs.h"

void bcs(cpu_t *cpu) {
	if (cpu->carry) {
		cpu->program_counter += cpu->operand;
	}
}