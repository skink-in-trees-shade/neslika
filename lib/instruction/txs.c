#include "txs.h"

void txs(struct cpu *cpu) {
	cpu->stack_pointer = cpu->x;
	cpu_zero(cpu, cpu->stack_pointer);
	cpu_negative(cpu, cpu->stack_pointer);
}