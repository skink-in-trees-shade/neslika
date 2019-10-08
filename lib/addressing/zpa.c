#include "zpa.h"

uint16_t zpa(cpu_t *cpu) {
	return cpu->memory[cpu->program_counter++];
}