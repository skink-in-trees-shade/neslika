#include "util.h"
#include "instruction/nop.h"
#include "nop.test.h"

void test_nop(void) {
	struct cpu *actual = cpu_random();
	struct cpu *expected = cpu_clone(actual);

	nop(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}