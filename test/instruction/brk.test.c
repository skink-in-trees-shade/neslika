#include <stdbool.h>
#include "util.h"
#include "instruction/brk.h"
#include "brk.test.h"

void test_brk(void) {
    cpu_t *actual = cpu_random();
    cpu_t *expected = cpu_clone(actual);
    expected->break_command = true;

    brk(actual);

    cpu_compare(expected, actual);

    cpu_destroy(expected);
    cpu_destroy(actual);
}