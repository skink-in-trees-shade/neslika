#include <assert.h>
#include "util.h"
#include "instruction/stx.h"
#include "stx.test.h"

void test_stx(void) {
	struct cpu *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->x = 0x48;

	struct cpu *expected = cpu_clone(actual);

	stx(actual);

	cpu_compare(expected, actual);
	assert(cpu_peek(actual, actual->operand_address) == actual->x);

	cpu_destroy(expected);
	cpu_destroy(actual);
}