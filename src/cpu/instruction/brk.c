#include <stdbool.h>
#include "brk.h"

void brk(struct cpu *cpu) {
	cpu->program_counter++;
	cpu_push(cpu, cpu->program_counter >> 8);
	cpu_push(cpu, cpu->program_counter & 0xFF);

	cpu->break_command = true;
	cpu_push(cpu, cpu_status(cpu));
	cpu->interrupt_disable = true;
	cpu->interrupt_disable_effective = true;
	cpu->interrupt_disable_shifter = 0x00;

	uint8_t low = cpu_peek(cpu, 0xFFFE);
	uint8_t high = cpu_peek(cpu, 0xFFFF);
	cpu->program_counter = (high << 8) + low;
}