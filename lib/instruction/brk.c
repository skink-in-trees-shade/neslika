#include <stdbool.h>
#include "brk.h"

void brk(cpu_t *cpu) {
	cpu->break_command = true;
}