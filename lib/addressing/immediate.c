#include "immediate.h"

uint16_t immediate(cpu_t *cpu) {
	return cpu->program_counter++;
}