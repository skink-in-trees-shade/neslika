#include <stdbool.h>
#include "util.h"
#include "instruction/bcc.h"
#include "bcc.test.h"

void test_bcc_carry_yes(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->carry = true;

	struct cpu *expected = cpu_clone(actual);

	bcc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_bcc_carry_no(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->program_counter = 0x78;

	bcc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}