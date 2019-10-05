#include "zpa.h"

uint8_t zpa(cpu_t *cpu) {
	uint8_t address = cpu->memory[cpu->program_counter++];
	return cpu->memory[address];
}