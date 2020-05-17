#include "nop.h"

void nop(struct cpu *cpu) {
	cpu->extra_execute_cycle = cpu->instruction & 0x0C;
}