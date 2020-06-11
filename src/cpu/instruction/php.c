#include "php.h"

void php(struct cpu *cpu) {
	cpu_push(cpu, cpu_status(cpu) | 0x10);
}