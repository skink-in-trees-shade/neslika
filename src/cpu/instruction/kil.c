#include "kil.h"
#include "error.h"

void kil(struct cpu *cpu) {
	(void)cpu;
	error("CPU halted.");
}