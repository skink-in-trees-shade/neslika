#include <stdbool.h>
#include "util.h"
#include "instruction/sed.h"
#include "sed.test.h"

void test_sed(void) {
	struct cpu *actual = cpu_random();
	struct cpu *expected = cpu_clone(actual);
	expected->decimal_mode = true;

	sed(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}