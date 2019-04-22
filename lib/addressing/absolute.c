#include "absolute.h"

uint16_t absolute(cpu_t *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	return (high << 8) + low;
}