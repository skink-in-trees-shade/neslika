#include "bpl.h"

void bpl(cpu_t *cpu) {
	if (!cpu->negative) {
		cpu->program_counter += cpu->operand;
	}
}