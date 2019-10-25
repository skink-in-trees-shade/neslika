#include <stdbool.h>
#include "util.h"
#include "instruction/bcs.h"
#include "bcs.test.h"

void test_bcs_carry_yes(void) {
	cpu_t *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->carry = true;

	cpu_t *expected = cpu_clone(actual);
	expected->program_counter = 0x78;

	bcs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_bcs_carry_no(void) {
	cpu_t *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->carry = false;

	cpu_t *expected = cpu_clone(actual);

	bcs(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}