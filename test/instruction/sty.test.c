#include <assert.h>
#include "util.h"
#include "instruction/sty.h"
#include "sty.test.h"

void test_sty(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->y = 0x48;

	cpu_t *expected = cpu_clone(actual);

	sty(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->y);

	cpu_destroy(expected);
	cpu_destroy(actual);
}