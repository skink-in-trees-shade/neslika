#include "dec.h"
#include "cmp.h"
#include "dcp.h"

void dcp(struct cpu *cpu) {
	dec(cpu);
	cmp(cpu);
}