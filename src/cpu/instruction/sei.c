#include <stdbool.h>
#include "sei.h"

void sei(struct cpu *cpu) {
	cpu->interrupt_disable = true;
}