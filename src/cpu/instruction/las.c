#include "las.h"

void las(struct cpu *cpu) {
	uint16_t value = cpu->operand & cpu->stack_pointer;
	cpu->accumulator = value;
	cpu->x = value;
	cpu->stack_pointer = value;
	cpu->extra_execute_cycle = true;
}