#include "zero_page_y.h"

uint16_t zero_page_y(cpu_t *cpu) {
	return cpu->memory[cpu->program_counter++] + cpu->y;
}