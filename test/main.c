#include "instruction/nop.test.h"
#include "runner.h"

int main(void) {
	runner_init();

	runner_test(test_nop);

	return 0;
}