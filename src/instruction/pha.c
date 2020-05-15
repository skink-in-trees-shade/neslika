#include "pha.h"

void pha(struct cpu *cpu) {
	cpu_push(cpu, cpu->accumulator);
}