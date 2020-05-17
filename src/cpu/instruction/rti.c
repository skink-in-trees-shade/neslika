#include "rti.h"

void rti(struct cpu *cpu) {
	cpu->status = cpu_pull(cpu) | 0x20;
	cpu->break_command = false;

	uint8_t low = cpu_pull(cpu);
	uint8_t high = cpu_pull(cpu);
	cpu->program_counter = (high << 8) + low;
}