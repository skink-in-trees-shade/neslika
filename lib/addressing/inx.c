#include "inx.h"

uint16_t inx(cpu_t *cpu) {
	uint8_t sub = cpu->memory[cpu->program_counter++];
	uint8_t high = cpu->memory[sub + cpu->x];
	uint8_t low = cpu->memory[sub + cpu->x + 1];
	return (high << 8) + low;
}