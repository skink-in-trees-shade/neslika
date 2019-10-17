#include "instruction/lda.test.h"
#include "instruction/nop.test.h"
#include "runner.h"

int main(void) {
	runner_init();

	runner_test(test_lda);
	runner_test(test_lda_zero);
	runner_test(test_lda_negative);

	runner_test(test_nop);

	return 0;
}