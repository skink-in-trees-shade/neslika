#include <stdint.h>
#include <assert.h>
#include "cpu.h"

void test_kil(void) {
	uint8_t rom[] = { 0x00 };

	cpu_t *cpu = cpu_new();
	cpu_load(cpu, rom, sizeof(rom));

    cpu_fetch(cpu);
    cpu_decode(cpu);
    cpu_execute(cpu);

    assert(!cpu->powered);

	cpu_destroy(cpu);
}