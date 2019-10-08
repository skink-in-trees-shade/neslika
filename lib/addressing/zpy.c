#include "zpy.h"

uint16_t zpy(cpu_t *cpu) {
	return cpu->memory[cpu->program_counter++] + cpu->y;
}