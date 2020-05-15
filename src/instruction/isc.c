#include "inc.h"
#include "sbc.h"
#include "isc.h"

void isc(struct cpu *cpu) {
	inc(cpu);
	sbc(cpu);
}