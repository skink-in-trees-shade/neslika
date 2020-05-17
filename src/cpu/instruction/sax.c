#include "sta.h"
#include "stx.h"
#include "sax.h"

void sax(struct cpu *cpu) {
	sta(cpu);
	stx(cpu);
	cpu_poke(cpu, cpu->operand, cpu->accumulator & cpu->x);
}