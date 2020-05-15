#include "stx.h"

void stx(struct cpu *cpu) {
	cpu_poke(cpu, cpu->operand_address, cpu->x);
}