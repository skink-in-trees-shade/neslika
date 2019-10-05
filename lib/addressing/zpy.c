#include "zpy.h"

uint8_t zpy(cpu_t *cpu) {
	uint8_t address = cpu->memory[cpu->program_counter++] + cpu->y;
	return cpu->memory[address];
}