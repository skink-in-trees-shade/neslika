#include "zpx.h"

uint16_t zpx(cpu_t *cpu) {
	return cpu->memory[cpu->program_counter++] + cpu->x;
}