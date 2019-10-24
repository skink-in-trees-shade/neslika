#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/abo.h"
#include "abo.test.h"

void test_abo(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	cpu->memory[cpu->program_counter + 1] = 0xF1;
	uint16_t expected = 0x24F1;

	uint16_t actual = abo(cpu);

	assert(expected == actual);

	cpu_destroy(cpu);
}

void test_abo_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 2;

	abo(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}