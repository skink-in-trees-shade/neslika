#include <stdbool.h>
#include "cli.h"

void cli(struct cpu *cpu) {
	cpu->interrupt_disable = false;
}