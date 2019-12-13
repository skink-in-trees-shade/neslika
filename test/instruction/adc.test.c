#include <stdbool.h>
#include "util.h"
#include "instruction/adc.h"
#include "adc.test.h"

void test_adc_no_carry_no_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x1A;
	actual->operand = 0x48;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x62;
	expected->carry = false;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = false;

	adc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_adc_carry_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xD0;
	actual->operand = 0x90;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x60;
	expected->carry = true;
	expected->overflow = true;
	expected->zero = false;
	expected->negative = false;

	adc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_adc_carry_no_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x50;
	actual->operand = 0xD0;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x20;
	expected->carry = true;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = false;

	adc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_adc_no_carry_overflow(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x50;
	actual->operand = 0x50;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0xA0;
	expected->carry = false;
	expected->overflow = true;
	expected->zero = false;
	expected->negative = true;

	adc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_adc_carry(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x1A;
	actual->operand = 0x48;
	actual->carry = true;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x63;
	expected->carry = false;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = false;

	adc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_adc_zero(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0x00;
	actual->operand = 0x00;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0x00;
	expected->carry = false;
	expected->overflow = false;
	expected->zero = true;
	expected->negative = false;

	adc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}

void test_adc_negative(void) {
	struct cpu *actual = cpu_random();
	actual->accumulator = 0xEA;
	actual->operand = 0x01;
	actual->carry = false;

	struct cpu *expected = cpu_clone(actual);
	expected->accumulator = 0xEB;
	expected->carry = false;
	expected->overflow = false;
	expected->zero = false;
	expected->negative = true;

	adc(actual);

	cpu_compare(expected, actual);

	cpu_destroy(expected);
	cpu_destroy(actual);
}