#include "cpu.test.h"
#include "addressing/abo.test.h"
#include "addressing/abx.test.h"
#include "addressing/aby.test.h"
#include "addressing/iix.test.h"
#include "addressing/iiy.test.h"
#include "addressing/imm.test.h"
#include "addressing/imp.test.h"
#include "addressing/zpa.test.h"
#include "addressing/zpx.test.h"
#include "addressing/zpy.test.h"
#include "instruction/and.test.h"
#include "instruction/brk.test.h"
#include "instruction/clc.test.h"
#include "instruction/cld.test.h"
#include "instruction/cli.test.h"
#include "instruction/clv.test.h"
#include "instruction/cmp.test.h"
#include "instruction/cpx.test.h"
#include "instruction/cpy.test.h"
#include "instruction/dec.test.h"
#include "instruction/dex.test.h"
#include "instruction/dey.test.h"
#include "instruction/eor.test.h"
#include "instruction/inc.test.h"
#include "instruction/inx.test.h"
#include "instruction/lda.test.h"
#include "instruction/ldx.test.h"
#include "instruction/ldy.test.h"
#include "instruction/nop.test.h"
#include "instruction/ora.test.h"
#include "instruction/sec.test.h"
#include "instruction/sed.test.h"
#include "instruction/sei.test.h"
#include "runner.h"

int main(void) {
	runner_init();

	runner_test(test_cpu_new);
	runner_test(test_cpu_load);
	runner_test(test_cpu_fetch);
	runner_test(test_cpu_decode);
	runner_test(test_cpu_execute);
	runner_test(test_cpu_negative_yes);
	runner_test(test_cpu_negative_no);
	runner_test(test_cpu_zero_yes);
	runner_test(test_cpu_zero_no);
	runner_test(test_cpu_running_yes);
	runner_test(test_cpu_running_no);

	runner_test(test_abo);
	runner_test(test_abo_program_counter);

	runner_test(test_abx);
	runner_test(test_abx_program_counter);

	runner_test(test_aby);
	runner_test(test_aby_program_counter);

	runner_test(test_iix);
	runner_test(test_iix_program_counter);

	runner_test(test_iiy);
	runner_test(test_iiy_program_counter);

	runner_test(test_imm);
	runner_test(test_imm_program_counter);

	runner_test(test_imp);

	runner_test(test_zpa);
	runner_test(test_zpa_program_counter);

	runner_test(test_zpx);
	runner_test(test_zpx_program_counter);

	runner_test(test_zpy);
	runner_test(test_zpy_program_counter);

	runner_test(test_and);
	runner_test(test_and_zero);
	runner_test(test_and_negative);

	runner_test(test_brk);

	runner_test(test_clc);

	runner_test(test_cld);

	runner_test(test_cli);

	runner_test(test_clv);

	runner_test(test_cmp_carry);
	runner_test(test_cmp_zero);
	runner_test(test_cmp_negative);

	runner_test(test_cpx_carry);
	runner_test(test_cpx_zero);
	runner_test(test_cpx_negative);

	runner_test(test_cpy_carry);
	runner_test(test_cpy_zero);
	runner_test(test_cpy_negative);

	runner_test(test_dec);
	runner_test(test_dec_zero);
	runner_test(test_dec_negative);

	runner_test(test_dex);
	runner_test(test_dex_zero);
	runner_test(test_dex_negative);

	runner_test(test_dey);
	runner_test(test_dey_zero);
	runner_test(test_dey_negative);

	runner_test(test_eor);
	runner_test(test_eor_zero);
	runner_test(test_eor_negative);

	runner_test(test_inc);
	runner_test(test_inc_zero);
	runner_test(test_inc_negative);

	runner_test(test_inx);
	runner_test(test_inx_zero);
	runner_test(test_inx_negative);

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

	runner_test(test_ora);
	runner_test(test_ora_zero);
	runner_test(test_ora_negative);

	runner_test(test_sec);

	runner_test(test_sed);

	runner_test(test_sei);

	return runner_report();
}