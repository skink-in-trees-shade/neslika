#include "adc.h"
#include "ror.h"
#include "rra.h"

void rra(struct cpu *cpu) {
	ror(cpu);
	adc(cpu);
}