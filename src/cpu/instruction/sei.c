#include <stdbool.h>
#include "sei.h"

void sei(struct cpu *cpu) {
	cpu->interrupt_disable = true;
	cpu->interrupt_disable_shifter |= 0x0C;
}