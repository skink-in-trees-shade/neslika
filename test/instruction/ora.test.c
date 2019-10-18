#include <stdbool.h>
#include "util.h"
#include "instruction/ora.h"
#include "ora.test.h"

void test_ora(void) {
    cpu_t *actual = cpu_random();
    actual->accumulator = 0x1A;
    actual->operand = 0x48;

    cpu_t *expected = cpu_clone(actual);
    expected->accumulator = 0x5A;
    expected->zero = false;
    expected->negative = false;

    ora(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}

void test_ora_zero(void) {
    cpu_t *actual = cpu_random();
    actual->accumulator = 0x00;
    actual->operand = 0x00;

    cpu_t *expected = cpu_clone(actual);
    expected->accumulator = 0x00;
    expected->zero = true;
    expected->negative = false;

    ora(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}

void test_ora_negative(void) {
    cpu_t *actual = cpu_random();
    actual->accumulator = 0xEA;
    actual->operand = 0xFD;

    cpu_t *expected = cpu_clone(actual);
    expected->accumulator = 0xFF;
    expected->zero = false;
    expected->negative = true;

    ora(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}