#include "abo.h"

void abo(struct cpu *cpu) {
	cpu->operand_low = cpu_read(cpu);
	cpu->operand_high = cpu_read(cpu);
}