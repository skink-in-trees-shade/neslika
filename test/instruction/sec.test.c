#include <stdbool.h>
#include "util.h"
#include "instruction/sec.h"
#include "sec.test.h"

void test_sec(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->carry = true;

	sec(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}