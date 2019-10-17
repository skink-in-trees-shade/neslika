#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/abx.h"
#include "abx.test.h"

void test_abx(void) {
    cpu_t *cpu = cpu_random();
    cpu->memory[cpu->program_counter] = 0x24;
    cpu->memory[cpu->program_counter + 1] = 0xF1;
    uint16_t expected = 0x24F1 + cpu->x;

    uint16_t actual = abx(cpu);

    assert(expected == actual);

    cpu_destroy(cpu);
}

void test_abx_program_counter(void) {
    cpu_t *cpu = cpu_random();
    uint16_t expected = cpu->program_counter + 2;

    abx(cpu);

    assert(cpu->program_counter == expected);

    cpu_destroy(cpu);
}