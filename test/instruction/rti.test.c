#include <stdbool.h>
#include "util.h"
#include "instruction/rti.h"
#include "rti.test.h"

void test_rti(void) {
	struct cpu *actual = cpu_random();
	cpu_push(actual, 0x25);
	cpu_push(actual, 0x4A);
	cpu_push(actual, 0x75);

	struct cpu *expected = cpu_clone(actual);
	expected->carry = true;
	expected->zero = false;
	expected->interrupt_disable = true;
	expected->decimal_mode = false;
	expected->break_command = false;
	expected->overflow = true;
	expected->negative = false;
	expected->program_counter = 0x254A;
	expected->stack_pointer = actual->stack_pointer + 3;

	rti(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}