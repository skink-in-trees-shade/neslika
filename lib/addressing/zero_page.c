#include "zero_page.h"

uint16_t zero_page(cpu_t *cpu) {
	return cpu->memory[cpu->program_counter++];
}