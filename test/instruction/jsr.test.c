#include <assert.h>
#include "util.h"
#include "instruction/jsr.h"
#include "jsr.test.h"

void test_jsr(void) {
	cpu_t *actual = cpu_random();
	actual->program_counter = 0x8A21;
	actual->stack_pointer = 0x47;
	actual->operand = 0x24;

	cpu_t *expected = cpu_clone(actual);
	expected->program_counter = 0x24;
	expected->stack_pointer = 0x45;

	jsr(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0x8A);
	assert(actual->memory[0x0146] == 0x20);

	cpu_destroy(expected);
	cpu_destroy(actual);
}