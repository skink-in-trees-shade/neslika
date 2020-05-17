#include "sax.h"

void sax(struct cpu *cpu) {
	cpu_poke(cpu, cpu->operand, cpu->accumulator);
	cpu_poke(cpu, cpu->operand, cpu->x);
	cpu_poke(cpu, cpu->operand, cpu->accumulator & cpu->x);
}