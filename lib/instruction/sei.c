#include <stdbool.h>
#include "sei.h"

void sei(cpu_t *cpu) {
	cpu->interrupt_disable = true;
}