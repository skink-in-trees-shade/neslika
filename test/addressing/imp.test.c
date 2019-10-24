#include <stdint.h>
#include <assert.h>
#include "util.h"
#include "addressing/imp.h"
#include "imp.test.h"

void test_imp(void) {
	cpu_t *cpu = cpu_random();
	uint16_t expected = 0;

	uint16_t actual = imp(cpu);

	assert(expected == actual);

	cpu_destroy(cpu);
}