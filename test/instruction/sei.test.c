#include <stdbool.h>
#include "util.h"
#include "instruction/sei.h"
#include "sei.test.h"

void test_sei(void) {
	cpu_t *actual = cpu_random();
	cpu_t *expected = cpu_clone(actual);
	expected->interrupt_disable = true;

	sei(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}