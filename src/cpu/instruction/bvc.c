#include <stdint.h>
#include "bvc.h"

void bvc(struct cpu *cpu) {
	if (!cpu->overflow) {
		cpu->program_counter += (int8_t)cpu->operand;
	}
}