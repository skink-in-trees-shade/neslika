#include "php.h"

void php(struct cpu *cpu) {
	cpu_push(cpu, cpu->status | 0x10);
}