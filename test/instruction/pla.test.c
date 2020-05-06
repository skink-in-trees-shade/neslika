#include <stdbool.h>
#include "util.h"
#include "instruction/pla.h"
#include "pla.test.h"

void test_pla(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->memory[0x0148] = 0x1A;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x1A;
	expected->stack_pointer = 0x48;
	expected->zero = false;
	expected->negative = false;

	pla(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_pla_zero(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->memory[0x0148] = 0x00;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x00;
	expected->stack_pointer = 0x48;
	expected->zero = true;
	expected->negative = false;

	pla(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_pla_negative(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->memory[0x0148] = 0xEA;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0xEA;
	expected->stack_pointer = 0x48;
	expected->zero = false;
	expected->negative = true;

	pla(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}