#include "pha.h"

void pha(cpu_t *cpu) {
	cpu_push(cpu, cpu->accumulator);
}