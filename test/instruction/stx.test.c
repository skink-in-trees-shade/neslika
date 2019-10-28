#include <assert.h>
#include "util.h"
#include "instruction/stx.h"
#include "stx.test.h"

void test_stx(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->x = 0x48;

	cpu_t *expected = cpu_clone(actual);

	stx(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->x);

	cpu_destroy(expected);
	cpu_destroy(actual);
}