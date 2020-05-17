#include "zpy.h"

void zpy(struct cpu *cpu) {
	cpu->operand = cpu_read(cpu);
	cpu->operand_low += cpu->y;
}