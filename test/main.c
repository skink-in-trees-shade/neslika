#include "addressing/abo.test.h"
#include "addressing/abx.test.h"
#include "addressing/aby.test.h"
#include "addressing/imm.test.h"
#include "addressing/imp.test.h"
#include "addressing/inx.test.h"
#include "addressing/iny.test.h"
#include "addressing/zpa.test.h"
#include "addressing/zpx.test.h"
#include "addressing/zpy.test.h"
#include "instruction/clc.test.h"
#include "instruction/cld.test.h"
#include "instruction/cli.test.h"
#include "instruction/clv.test.h"
#include "instruction/lda.test.h"
#include "instruction/ldx.test.h"
#include "instruction/ldy.test.h"
#include "instruction/nop.test.h"
#include "instruction/sec.test.h"
#include "runner.h"

int main(void) {
	runner_init();

	runner_test(test_abo);
	runner_test(test_abo_program_counter);

	runner_test(test_abx);
	runner_test(test_abx_program_counter);

	runner_test(test_aby);
	runner_test(test_aby_program_counter);

	runner_test(test_imm);
	runner_test(test_imm_program_counter);

	runner_test(test_imp);

	runner_test(test_inx);
	runner_test(test_inx_program_counter);

	runner_test(test_iny);
	runner_test(test_iny_program_counter);

	runner_test(test_zpa);
	runner_test(test_zpa_program_counter);

	runner_test(test_zpx);
	runner_test(test_zpx_program_counter);

	runner_test(test_zpy);
	runner_test(test_zpy_program_counter);

	runner_test(test_clc);

	runner_test(test_cld);

	runner_test(test_cli);

	runner_test(test_clv);

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

	runner_test(test_sec);

	return 0;
}