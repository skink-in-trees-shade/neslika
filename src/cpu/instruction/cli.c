#include <stdbool.h>
#include "cli.h"

void cli(struct cpu *cpu) {
	cpu->interrupt_disable = false;
	cpu->interrupt_disable_shifter |= 0x04;
}