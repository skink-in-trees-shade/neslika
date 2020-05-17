#include "plp.h"

void plp(struct cpu *cpu) {
	cpu->status = (cpu_pull(cpu) | 0x20) & 0xEF;
}