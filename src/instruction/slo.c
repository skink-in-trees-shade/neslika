#include "asl.h"
#include "ora.h"
#include "slo.h"

void slo(struct cpu *cpu) {
	asl(cpu);
	ora(cpu);
}