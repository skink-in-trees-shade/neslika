#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/imm.h"
#include "imm.test.h"

void test_imm(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter;

	uint16_t actual = imm(cpu);

	assert(expected == actual);

	cpu_destroy(cpu);
}

void test_imm_program_counter(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = cpu->program_counter + 1;

	imm(cpu);

	assert(cpu->program_counter == expected);

	cpu_destroy(cpu);
}