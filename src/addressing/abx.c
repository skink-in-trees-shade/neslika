#include "abo.h"
#include "abx.h"

void abx(struct cpu *cpu) {
	abo(cpu);
	cpu->operand += cpu->x;
}