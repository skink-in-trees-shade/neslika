#include <stdint.h>
#include "cpu.h"
#include "ines.h"
#include "debug.h"

const char *test_rom = "./assets/nestest.nes";

int main(void) {
	struct cpu *cpu = cpu_new();
	ines_load(cpu, test_rom);
	cpu->program_counter = 0xC000;

	do {
		cpu_fetch(cpu);
		cpu_decode(cpu);
		cpu_debug(cpu);
		cpu_execute(cpu);
	} while (cpu_running(cpu));

	cpu_destroy(cpu);
	return 0;
}