#include <stdbool.h>
#include "util.h"
#include "instruction/sei.h"
#include "sei.test.h"

void test_sei(void) {
	struct cpu *actual = cpu_random();
	struct cpu *expected = cpu_clone(actual);
	expected->interrupt_disable = true;

	sei(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}