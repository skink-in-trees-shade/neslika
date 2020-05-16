#include "abo.h"
#include "aby.h"

void aby(struct cpu *cpu) {
	abo(cpu);
	cpu->operand += cpu->y;
}