#include <stdbool.h>
#include "util.h"
#include "instruction/plp.h"
#include "plp.test.h"

void test_plp_carry(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x46;
	cpu_poke(actual, 0x0147, 0x31);

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = 0x47;
	expected->carry = true;
	expected->zero = false;
	expected->interrupt_disable = false;
	expected->decimal_mode = false;
	expected->overflow = false;
	expected->negative = false;

	plp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_plp_zero(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x46;
	cpu_poke(actual, 0x0147, 0x32);

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = 0x47;
	expected->carry = false;
	expected->zero = true;
	expected->interrupt_disable = false;
	expected->decimal_mode = false;
	expected->overflow = false;
	expected->negative = false;

	plp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_plp_interrupt_disable(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x46;
	cpu_poke(actual, 0x0147, 0x34);

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = 0x47;
	expected->carry = false;
	expected->zero = false;
	expected->interrupt_disable = true;
	expected->decimal_mode = false;
	expected->overflow = false;
	expected->negative = false;

	plp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_plp_decimal_mode(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x46;
	cpu_poke(actual, 0x0147, 0x38);

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = 0x47;
	expected->carry = false;
	expected->zero = false;
	expected->interrupt_disable = false;
	expected->decimal_mode = true;
	expected->overflow = false;
	expected->negative = false;

	plp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_plp_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x46;
	cpu_poke(actual, 0x0147, 0x70);

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = 0x47;
	expected->carry = false;
	expected->zero = false;
	expected->interrupt_disable = false;
	expected->decimal_mode = false;
	expected->overflow = true;
	expected->negative = false;

	plp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_plp_negative(void) {
	struct cpu *actual = cpu_random();
	actual->stack_pointer = 0x46;
	cpu_poke(actual, 0x0147, 0xB0);

	struct cpu *expected = cpu_clone(actual);
	expected->stack_pointer = 0x47;
	expected->carry = false;
	expected->zero = false;
	expected->interrupt_disable = false;
	expected->decimal_mode = false;
	expected->overflow = false;
	expected->negative = true;

	plp(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}