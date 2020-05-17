#include "php.h"

void php(struct cpu *cpu) {
	uint8_t status = 0
		| (cpu->carry << 0)
		| (cpu->zero << 1)
		| (cpu->interrupt_disable << 2)
		| (cpu->decimal_mode << 3)
		| (1 << 4)
		| (1 << 5)
		| (cpu->overflow << 6)
		| (cpu->negative << 7);
	cpu_push(cpu, status);
}