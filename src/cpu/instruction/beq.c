#include <stdint.h>
#include "beq.h"

void beq(struct cpu *cpu) {
	if (cpu->zero) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}