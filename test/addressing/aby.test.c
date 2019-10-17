#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/aby.h"
#include "aby.test.h"

void test_aby(void) {
    cpu_t *cpu = cpu_random();
    cpu->memory[cpu->program_counter] = 0x24;
    cpu->memory[cpu->program_counter + 1] = 0xF1;
    uint16_t expected = 0x24F1 + cpu->y;

    uint16_t actual = aby(cpu);

    assert(expected == actual);

    cpu_destroy(cpu);
}

void test_aby_program_counter(void) {
    cpu_t *cpu = cpu_random();
    uint16_t expected = cpu->program_counter + 2;

    aby(cpu);

    assert(cpu->program_counter == expected);

    cpu_destroy(cpu);
}