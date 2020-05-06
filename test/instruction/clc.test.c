#include <stdbool.h>
#include "util.h"
#include "instruction/clc.h"
#include "clc.test.h"

void test_clc(void) {
	struct cpu *actual = cpu_random();
	struct cpu *expected = cpu_clone(actual);
	expected->carry = false;

	clc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}