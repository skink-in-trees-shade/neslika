#include "absolute_y.h"

uint16_t absolute_y(cpu_t *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	return (high << 8) + low + cpu->y;
}