#include <stdbool.h>
#include "util.h"
#include "instruction/cli.h"
#include "cli.test.h"

void test_cli(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->interrupt_disable = false;

	cli(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}