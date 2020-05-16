#include "zpa.h"
#include "zpx.h"

void zpx(struct cpu *cpu) {
	zpa(cpu);
	cpu->operand_low += cpu->x;
}