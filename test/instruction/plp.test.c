#include <stdbool.h>
#include "util.h"
#include "instruction/plp.h"
#include "plp.test.h"

void test_plp_carry(void) {
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x46;
	actual->memory[0x0147] = 0x31;

	cpu_t *expected = cpu_clone(actual);
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
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x46;
	actual->memory[0x0147] = 0x32;

	cpu_t *expected = cpu_clone(actual);
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
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x46;
	actual->memory[0x0147] = 0x34;

	cpu_t *expected = cpu_clone(actual);
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
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x46;
	actual->memory[0x0147] = 0x38;

	cpu_t *expected = cpu_clone(actual);
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
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x46;
	actual->memory[0x0147] = 0x70;

	cpu_t *expected = cpu_clone(actual);
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
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x46;
	actual->memory[0x0147] = 0xB0;

	cpu_t *expected = cpu_clone(actual);
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