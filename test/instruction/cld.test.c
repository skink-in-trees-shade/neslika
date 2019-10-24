#include <stdbool.h>
#include "util.h"
#include "instruction/cld.h"
#include "cld.test.h"

void test_cld(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->decimal_mode = false;

	cld(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}