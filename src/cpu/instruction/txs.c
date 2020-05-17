#include "txs.h"

void txs(struct cpu *cpu) {
	cpu->stack_pointer = cpu->x;
}