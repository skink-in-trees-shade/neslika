#include "abx.h"

uint16_t abx(cpu_t *cpu) {
	uint8_t high = cpu->memory[cpu->program_counter++];
	uint8_t low = cpu->memory[cpu->program_counter++];
	return (high << 8) + low + cpu->x;
}