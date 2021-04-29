#include "rti.h"

void rti(struct cpu *cpu) {
	uint8_t status = cpu_pull(cpu);
	cpu->carry = (status >> 0) & 0x01;
	cpu->zero = (status >> 1) & 0x01;
	cpu->interrupt_disable = (status >> 2) & 0x01;
	cpu->decimal_mode = (status >> 3) & 0x01;
	cpu->break_command = false;
	cpu->overflow = (status >> 6) & 0x01;
	cpu->negative = (status >> 7) & 0x01;

	uint8_t low = cpu_pull(cpu);
	uint8_t high = cpu_pull(cpu);
	cpu->program_counter = (high << 8) + low;

	cpu->interrupt_disable_effective = cpu->interrupt_disable;
	cpu->interrupt_disable_shifter = 0x00;
}