#include <assert.h>
#include "util.h"
#include "instruction/sta.h"
#include "sta.test.h"

void test_sta(void) {
	cpu_t *actual = cpu_random();
	actual->operand_address = 0xE7;
	actual->accumulator = 0x48;

	cpu_t *expected = cpu_clone(actual);

	sta(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[actual->operand_address] == actual->accumulator);

	cpu_destroy(expected);
	cpu_destroy(actual);
}