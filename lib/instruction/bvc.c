#include "bvc.h"

void bvc(cpu_t *cpu) {
	if (!cpu->overflow) {
		cpu->program_counter += cpu->operand;
	}
}