#include "tay.h"

void tay(cpu_t *cpu) {
	cpu->y = cpu->accumulator;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}