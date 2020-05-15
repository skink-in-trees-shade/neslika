#include <stdbool.h>
#include "util.h"
#include "instruction/txs.h"
#include "txs.test.h"

void test_txs(void) {
	struct cpu *actual = cpu_random();
	actual->x = 0x48;

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = actual->x;

	txs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}