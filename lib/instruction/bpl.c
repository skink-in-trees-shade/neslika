#include <stdint.h>
#include "bpl.h"

void bpl(struct cpu *cpu) {
	if (!cpu->negative) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}