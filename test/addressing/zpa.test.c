#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/zpa.h"
#include "zpa.test.h"

void test_zpa(void) {
	cpu_t *cpu = cpu_random();
	cpu->memory[cpu->program_counter] = 0x24;
	uint16_t expected = 0x24;

	uint16_t actual = zpa(cpu);

	assert(expected == actual);

	cpu_destroy(cpu);
}

void test_zpa_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	zpa(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}