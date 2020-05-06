#include "bcc.h"

void bcc(struct cpu *cpu) {
	if (!cpu->carry) {
		cpu->program_counter += cpu->operand;
	}
}