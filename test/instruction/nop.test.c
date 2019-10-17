#include "util.h"
#include "instruction/nop.h"
#include "nop.test.h"

void test_nop(void) {
    cpu_t *actual = cpu_random();
    cpu_t *expected = cpu_clone(actual);

    nop(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}