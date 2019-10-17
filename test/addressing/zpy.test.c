#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/zpy.h"
#include "zpy.test.h"

void test_zpy(void) {
    cpu_t *cpu = cpu_random();
    cpu->memory[cpu->program_counter] = 0x24;
    uint16_t expected = 0x24 + cpu->y;

    uint16_t actual = zpy(cpu);

    assert(expected == actual);

    cpu_destroy(cpu);
}

void test_zpy_program_counter(void) {
    cpu_t *cpu = cpu_random();
    uint16_t expected = cpu->program_counter + 1;

    zpy(cpu);

    assert(cpu->program_counter == expected);

    cpu_destroy(cpu);
}