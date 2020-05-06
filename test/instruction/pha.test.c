#include <assert.h>
#include "util.h"
#include "instruction/pha.h"
#include "pha.test.h"

void test_pha(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xA3;
	actual->stack_pointer = 0x47;

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = 0x46;

	pha(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0xA3);

	cpu_destroy(expected);
	cpu_destroy(actual);
}