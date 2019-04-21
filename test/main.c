#include "cpu.h"

static void test(void) {
	cpu_t *cpu = cpu_new();
	cpu_run(cpu);
	cpu_destroy(cpu);
}

int main(void) {
	test();
	return 0;
}