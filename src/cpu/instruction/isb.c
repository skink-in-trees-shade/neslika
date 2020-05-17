#include "inc.h"
#include "sbc.h"
#include "isb.h"

void isb(struct cpu *cpu) {
	inc(cpu);
	sbc(cpu);
}