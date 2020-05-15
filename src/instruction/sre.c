#include "eor.h"
#include "lsr.h"
#include "sre.h"

void sre(struct cpu *cpu) {
	lsr(cpu);
	eor(cpu);
}