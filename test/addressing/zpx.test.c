#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/zpx.h"
#include "zpx.test.h"

void test_zpx(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	uint16_t expected = 0x24 + cpu->x;

	uint16_t actual = zpx(cpu);

	assert(expected == actual);

	cpu_destroy(cpu);
}

void test_zpx_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	zpx(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}