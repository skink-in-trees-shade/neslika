#include "inx.h"

void inx(cpu_t *cpu) {
	cpu->x++;
	cpu_zero(cpu, cpu->x);
	cpu_negative(cpu, cpu->x);
}