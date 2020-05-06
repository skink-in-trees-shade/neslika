#include <stdbool.h>
#include "util.h"
#include "instruction/beq.h"
#include "beq.test.h"

void test_beq_zero_yes(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->zero = true;

	struct cpu *expected = cpu_clone(actual);
	expected->program_counter = 0x78;

	beq(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_beq_zero_no(void) {
	struct cpu *actual = cpu_random();
	actual->program_counter = 0x54;
	actual->operand = 0x24;
	actual->zero = false;

	struct cpu *expected = cpu_clone(actual);

	beq(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}