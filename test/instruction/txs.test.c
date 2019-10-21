#include <stdbool.h>
#include "util.h"
#include "instruction/txs.h"
#include "txs.test.h"

void test_txs(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0x48;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = actual->x;
	expected->zero = false;
	expected->negative = false;

	txs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_txs_zero(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0x00;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = actual->x;
	expected->zero = true;
	expected->negative = false;

	txs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_txs_negative(void) {
	cpu_t *actual = cpu_random();
	actual->x = 0xF8;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = actual->x;
	expected->zero = false;
	expected->negative = true;

	txs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}