#include <stdbool.h>
#include "util.h"
#include "instruction/sec.h"
#include "sec.test.h"

void test_sec(void) {
	struct cpu *actual = cpu_random();
	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;

	sec(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}