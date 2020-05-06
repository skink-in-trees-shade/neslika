#include "bvc.h"

void bvc(struct cpu *cpu) {
	if (!cpu->overflow) {
		cpu->program_counter += cpu->operand;
	}
}