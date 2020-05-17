#include <stdbool.h>
#include "brk.h"

void brk(struct cpu *cpu) {
	uint8_t high = (cpu->program_counter >> 8) & 0xFF;
	uint8_t low = cpu->program_counter & 0xFF;
	uint8_t status = 0
		| (cpu->carry << 0)
		| (cpu->zero << 1)
		| (cpu->interrupt_disable << 2)
		| (cpu->decimal_mode << 3)
		| (1 << 4)
		| (1 << 5)
		| (cpu->overflow << 6)
		| (cpu->negative << 7);
	cpu_push(cpu, high);
	cpu_push(cpu, low);
	cpu_push(cpu, status);

	low = cpu_peek(cpu, 0xFFFE);
	high = cpu_peek(cpu, 0xFFFF);
	cpu->program_counter = (high << 8) + low;

	cpu->break_command = true;
}