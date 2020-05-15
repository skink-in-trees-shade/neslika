#include "zpa.h"

void zpa(struct cpu *cpu) {
	cpu->operand_address = cpu_read(cpu);
	cpu->operand = cpu_peek(cpu, cpu->operand_address);
}