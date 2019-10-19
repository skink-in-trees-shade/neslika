#include "dey.h"

void dey(cpu_t *cpu) {
	cpu->y--;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}