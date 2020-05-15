#include <stdint.h>
#include "bne.h"

void bne(struct cpu *cpu) {
	if (!cpu->zero) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}