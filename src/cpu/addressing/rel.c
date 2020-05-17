#include "rel.h"

void rel(struct cpu *cpu) {
	cpu->operand = cpu_read(cpu);
}