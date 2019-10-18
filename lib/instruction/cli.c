#include <stdbool.h>
#include "cli.h"

void cli(cpu_t *cpu) {
	cpu->interrupt_disable = false;
}