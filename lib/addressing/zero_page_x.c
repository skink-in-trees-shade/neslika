#include "zero_page_x.h"

uint16_t zero_page_x(cpu_t *cpu) {
	return cpu->memory[cpu->program_counter++] + cpu->x;
}