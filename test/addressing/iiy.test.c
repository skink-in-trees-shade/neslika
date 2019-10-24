#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/iiy.h"
#include "iiy.test.h"

void test_iiy(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x84;
	cpu->memory[0x84] = 0x24;
	cpu->memory[0x85] = 0xF1;
	uint16_t expected = 0x24F1 + cpu->y;

	uint16_t actual = iiy(cpu);

	assert(expected == actual);

	cpu_destroy(cpu);
}

void test_iiy_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	iiy(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}