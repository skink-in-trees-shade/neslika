#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/iix.h"
#include "iix.test.h"

void test_iix(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x84;
	cpu->memory[0x84 + cpu->x] = 0x24;
	cpu->memory[0x85 + cpu->x] = 0xF1;
	uint16_t expected = 0x24F1;

	uint16_t actual = iix(cpu);

	assert(expected == actual);

	cpu_destroy(cpu);
}

void test_iix_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	iix(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}