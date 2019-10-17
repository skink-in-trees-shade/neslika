#include <stdbool.h>
#include "util.h"
#include "instruction/lda.h"
#include "lda.test.h"

void test_lda(void) {
    cpu_t *actual = cpu_random();
    actual->operand = 0x48;

    cpu_t *expected = cpu_clone(actual);
    expected->accumulator = actual->operand;
    expected->zero = false;
    expected->negative = false;

    lda(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}

void test_lda_zero(void) {
    cpu_t *actual = cpu_random();
    actual->operand = 0x00;

    cpu_t *expected = cpu_clone(actual);
    expected->accumulator = actual->operand;
    expected->zero = true;
    expected->negative = false;

    lda(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}

void test_lda_negative(void) {
    cpu_t *actual = cpu_random();
    actual->operand = 0xF8;

    cpu_t *expected = cpu_clone(actual);
    expected->accumulator = actual->operand;
    expected->zero = false;
    expected->negative = true;

    lda(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}