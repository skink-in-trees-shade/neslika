#include "zpa.h"

void zpa(struct cpu *cpu) {
	cpu->operand = cpu_read(cpu);
}