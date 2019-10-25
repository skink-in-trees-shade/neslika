#include "bne.h"

void bne(cpu_t *cpu) {
	if (!cpu->zero) {
		cpu->program_counter += cpu->operand;
	}
}