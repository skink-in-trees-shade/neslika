#include "zpa.h"
#include "zpy.h"

void zpy(struct cpu *cpu) {
	zpa(cpu);
	cpu->operand_low += cpu->y;
}