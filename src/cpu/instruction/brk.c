#include <stdbool.h>
#include "brk.h"

void brk(struct cpu *cpu) {
	uint8_t high = (cpu->program_counter >> 8) & 0xFF;
	uint8_t low = cpu->program_counter & 0xFF;
	cpu_push(cpu, high);
	cpu_push(cpu, low);
	
	cpu->break_command = true;
	cpu_push(cpu, cpu->status);

	low = cpu_peek(cpu, 0xFFFE);
	high = cpu_peek(cpu, 0xFFFF);
	cpu->program_counter = (high << 8) + low;
}