#include "bcc.h"

void bcc(cpu_t *cpu) {
	if (!cpu->carry) {
		cpu->program_counter += cpu->operand;
	}
}