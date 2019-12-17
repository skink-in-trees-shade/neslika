#include <stdbool.h>
#include "brk.h"

void brk(cpu_t *cpu) {
	uint8_t old_high = (cpu->program_counter >> 8) & 0xFF;
	uint8_t old_low = cpu->program_counter & 0xFF;
	uint8_t status = 0
		| (cpu->carry << 0)
		| (cpu->zero << 1)
		| (cpu->interrupt_disable << 2)
		| (cpu->decimal_mode << 3)
		| (1 << 4)
		| (1 << 5)
		| (cpu->overflow << 6)
		| (cpu->negative << 7);
	cpu_push(cpu, old_high);
	cpu_push(cpu, old_low);
	cpu_push(cpu, status);

	uint8_t new_high = cpu->memory[0xFFFE];
	uint8_t new_low = cpu->memory[0xFFFF];
	cpu->program_counter = (new_high << 8) + new_low;

	cpu->break_command = true;
}