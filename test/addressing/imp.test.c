#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/imp.h"
#include "addressing_mode.h"
#include "imp.test.h"

void test_imp_address_mode(void) {
	cpu_t *cpu = cpu_random();
	addressing_mode_t expected = addressing_implicit;

	imp(cpu);

	assert(cpu->addressing_mode == expected);

	cpu_destroy(cpu);
}