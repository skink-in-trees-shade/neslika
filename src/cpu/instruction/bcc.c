#include <stdint.h>
#include "bcc.h"

void bcc(struct cpu *cpu) {
	if (!cpu->carry) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}