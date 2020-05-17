#include "zpx.h"

void zpx(struct cpu *cpu) {
	cpu->operand = cpu_read(cpu);
	cpu->operand_low += cpu->x;
}