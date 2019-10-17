#include "addressing/imm.test.h"
#include "addressing/imp.test.h"
#include "instruction/lda.test.h"
#include "instruction/ldx.test.h"
#include "instruction/ldy.test.h"
#include "instruction/nop.test.h"
#include "runner.h"

int main(void) {
	runner_init();

	runner_test(test_imm);
	runner_test(test_imm_program_counter);

	runner_test(test_imp);

	runner_test(test_lda);
	runner_test(test_lda_zero);
	runner_test(test_lda_negative);

	runner_test(test_ldx);
	runner_test(test_ldx_zero);
	runner_test(test_ldx_negative);

	runner_test(test_ldy);
	runner_test(test_ldy_zero);
	runner_test(test_ldy_negative);

	runner_test(test_nop);

	return 0;
}