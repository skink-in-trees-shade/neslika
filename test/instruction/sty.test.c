#include <assert.h>
#include "util.h"
#include "instruction/sty.h"
#include "sty.test.h"

void test_sty(void) {
	struct cpu *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->y = 0x48;

	struct cpu *expected = cpu_clone(actual);

	sty(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->y);

	cpu_destroy(expected);
	cpu_destroy(actual);
}