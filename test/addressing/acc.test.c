#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/acc.h"
#include "addressing_mode.h"
#include "acc.test.h"

void test_acc_address_mode(void) {
	struct cpu *cpu = cpu_random();
	enum addressing_mode expected = addressing_accumulator;

	acc(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}