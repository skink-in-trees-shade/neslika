#include "inx.h"

uint8_t inx(cpu_t *cpu) {
	uint8_t sub = cpu->memory[cpu->program_counter++];
	uint8_t high = cpu->memory[sub + cpu->x];
	uint8_t low = cpu->memory[sub + cpu->x + 1];
	uint8_t address = (high << 8) + low;
	return cpu->memory[address];
}