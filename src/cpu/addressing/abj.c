#include "abj.h"

void abj(struct cpu *cpu) {
	cpu->operand_low = cpu_read(cpu);
	cpu->operand_high = cpu_read(cpu);
}