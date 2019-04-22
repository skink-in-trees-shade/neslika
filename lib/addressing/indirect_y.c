#include "indirect_y.h"

uint16_t indirect_y(cpu_t *cpu) {
	uint8_t sub = cpu->memory[cpu->program_counter++];
	uint8_t high = cpu->memory[sub];
	uint8_t low = cpu->memory[sub + 1];
	return (high << 8) + low + cpu->y;
}