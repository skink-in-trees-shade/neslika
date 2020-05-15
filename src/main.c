#include <stdint.h>
#include "cpu.h"

int main(void) {
	struct cpu *cpu = cpu_new();

	uint8_t rom[] = { 0x08, 0x28, 0xEA, 0x00 };

	cpu_load(cpu, rom, sizeof(rom));

	while (cpu->instruction != 0x00) {
		cpu_fetch(cpu);
		cpu_decode(cpu);
		cpu_execute(cpu);
	}

	cpu_destroy(cpu);
	return 0;
}