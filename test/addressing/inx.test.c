#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/inx.h"
#include "inx.test.h"

void test_inx(void) {
    cpu_t *cpu = cpu_random();
    cpu->memory[cpu->program_counter] = 0x84;
    cpu->memory[0x84 + cpu->x] = 0x24;
    cpu->memory[0x85 + cpu->x] = 0xF1;
    uint16_t expected = 0x24F1;

    uint16_t actual = inx(cpu);

    assert(expected == actual);

    cpu_destroy(cpu);
}

void test_inx_program_counter(void) {
    cpu_t *cpu = cpu_random();
    uint16_t expected = cpu->program_counter + 1;

    inx(cpu);

    assert(cpu->program_counter == expected);

    cpu_destroy(cpu);
}