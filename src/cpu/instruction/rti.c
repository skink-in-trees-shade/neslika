#include <stdbool.h>
#include "rti.h"

void rti(struct cpu *cpu) {
	uint8_t status = cpu_pull(cpu);
	uint8_t low = cpu_pull(cpu);
	uint8_t high = cpu_pull(cpu);

	cpu->carry = status >> 0 & 1;
	cpu->zero = status >> 1 & 1;
	cpu->interrupt_disable = status >> 2 & 1;
	cpu->decimal_mode = status >> 3 & 1;
	cpu->break_command = false;
	cpu->overflow = status >> 6 & 1;
	cpu->negative = status >> 7 & 1;
	cpu->program_counter = (high << 8) + low;
}