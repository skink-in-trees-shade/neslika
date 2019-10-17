#include <stdbool.h>
#include "util.h"
#include "instruction/ldx.h"
#include "ldx.test.h"

void test_ldx(void) {
    cpu_t *actual = cpu_random();
    actual->operand = 0x48;

    cpu_t *expected = cpu_clone(actual);
    expected->x = actual->operand;
    expected->zero = false;
    expected->negative = false;

    ldx(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}

void test_ldx_zero(void) {
    cpu_t *actual = cpu_random();
    actual->operand = 0x00;

    cpu_t *expected = cpu_clone(actual);
    expected->x = actual->operand;
    expected->zero = true;
    expected->negative = false;

    ldx(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}

void test_ldx_negative(void) {
    cpu_t *actual = cpu_random();
    actual->operand = 0xF8;

    cpu_t *expected = cpu_clone(actual);
    expected->x = actual->operand;
    expected->zero = false;
    expected->negative = true;

    ldx(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}