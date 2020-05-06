#include <stdbool.h>
#include "util.h"
#include "instruction/clv.h"
#include "clv.test.h"

void test_clv(void) {
	struct cpu *actual = cpu_random();
	struct cpu *expected = cpu_clone(actual);
	expected->overflow = false;

	clv(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}