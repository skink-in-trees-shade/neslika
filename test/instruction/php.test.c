#include <stdbool.h>
#include <assert.h>
#include "util.h"
#include "instruction/php.h"
#include "php.test.h"

void test_php_carry(void) {
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->carry = true;
	actual->zero = false;
	actual->interrupt_disable = false;
	actual->decimal_mode = false;
	actual->overflow = false;
	actual->negative = false;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = 0x46;

	php(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0x31);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_php_zero(void) {
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->carry = false;
	actual->zero = true;
	actual->interrupt_disable = false;
	actual->decimal_mode = false;
	actual->overflow = false;
	actual->negative = false;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = 0x46;

	php(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0x32);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_php_interrupt_disable(void) {
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->carry = false;
	actual->zero = false;
	actual->interrupt_disable = true;
	actual->decimal_mode = false;
	actual->overflow = false;
	actual->negative = false;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = 0x46;

	php(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0x34);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_php_decimal_mode(void) {
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->carry = false;
	actual->zero = false;
	actual->interrupt_disable = false;
	actual->decimal_mode = true;
	actual->overflow = false;
	actual->negative = false;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = 0x46;

	php(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0x38);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_php_overflow(void) {
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->carry = false;
	actual->zero = false;
	actual->interrupt_disable = false;
	actual->decimal_mode = false;
	actual->overflow = true;
	actual->negative = false;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = 0x46;

	php(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0x70);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_php_negative(void) {
	cpu_t *actual = cpu_random();
	actual->stack_pointer = 0x47;
	actual->carry = false;
	actual->zero = false;
	actual->interrupt_disable = false;
	actual->decimal_mode = false;
	actual->overflow = false;
	actual->negative = true;

	cpu_t *expected = cpu_clone(actual);
	expected->stack_pointer = 0x46;

	php(actual);

	cpu_compare(expected, actual);
	assert(actual->memory[0x0147] == 0xB0);

	cpu_destroy(expected);
	cpu_destroy(actual);
}