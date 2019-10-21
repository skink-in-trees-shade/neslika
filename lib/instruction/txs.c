#include "txs.h"

void txs(cpu_t *cpu) {
	cpu->stack_pointer = cpu->x;
	cpu_zero(cpu, cpu->stack_pointer);
	cpu_negative(cpu, cpu->stack_pointer);
}