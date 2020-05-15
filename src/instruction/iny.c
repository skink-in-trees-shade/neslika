#include "iny.h"

void iny(struct cpu *cpu) {
	cpu->y++;
	cpu_zero(cpu, cpu->y);
	cpu_negative(cpu, cpu->y);
}