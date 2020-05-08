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
#include "instruction/asl.test.h"
#include "instruction/bcc.test.h"
#include "instruction/bcs.test.h"
#include "instruction/beq.test.h"
#include "instruction/bit.test.h"
#include "instruction/bmi.test.h"
#include "instruction/bne.test.h"
#include "instruction/bpl.test.h"
#include "instruction/brk.test.h"
#include "instruction/bvc.test.h"
#include "instruction/bvs.test.h"
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
#include "instruction/iny.test.h"
#include "instruction/jmp.test.h"
#include "instruction/jsr.test.h"
#include "instruction/lda.test.h"
#include "instruction/ldx.test.h"
#include "instruction/ldy.test.h"
#include "instruction/lsr.test.h"
#include "instruction/nop.test.h"
#include "instruction/ora.test.h"
#include "instruction/pha.test.h"
#include "instruction/php.test.h"
#include "instruction/pla.test.h"
#include "instruction/plp.test.h"
#include "instruction/rol.test.h"
#include "instruction/ror.test.h"
#include "instruction/rti.test.h"
#include "instruction/rts.test.h"
#include "instruction/sec.test.h"
#include "instruction/sed.test.h"
#include "instruction/sei.test.h"
#include "instruction/sta.test.h"
#include "instruction/stx.test.h"
#include "instruction/sty.test.h"
#include "instruction/tax.test.h"
#include "instruction/tay.test.h"
#include "instruction/tsx.test.h"
#include "instruction/txa.test.h"
#include "instruction/txs.test.h"
#include "instruction/tya.test.h"
#include "runner.h"

int main(void) {
	runner_init();

	runner_test(test_cpu_new);
	runner_test(test_cpu_load);
	runner_test(test_cpu_fetch);
	runner_test(test_cpu_decode);
	runner_test(test_cpu_execute);
	runner_test(test_cpu_zero_yes);
	runner_test(test_cpu_zero_no);
	runner_test(test_cpu_negative_yes);
	runner_test(test_cpu_negative_no);
	runner_test(test_cpu_read);
	runner_test(test_cpu_read_program_counter);
	runner_test(test_cpu_peek);
	runner_test(test_cpu_poke);
	runner_test(test_cpu_push);
	runner_test(test_cpu_pull);
	runner_test(test_cpu_running_yes);
	runner_test(test_cpu_running_no);

	runner_test(test_abo_operand);
	runner_test(test_abo_operand_address);
	runner_test(test_abo_address_mode);
	runner_test(test_abo_program_counter);

	runner_test(test_abx_operand);
	runner_test(test_abx_operand_address);
	runner_test(test_abx_address_mode);
	runner_test(test_abx_program_counter);

	runner_test(test_aby_operand);
	runner_test(test_aby_operand_address);
	runner_test(test_aby_address_mode);
	runner_test(test_aby_program_counter);

	runner_test(test_iix_operand);
	runner_test(test_iix_operand_address);
	runner_test(test_iix_address_mode);
	runner_test(test_iix_program_counter);

	runner_test(test_iiy_operand);
	runner_test(test_iiy_operand_address);
	runner_test(test_iiy_address_mode);
	runner_test(test_iiy_program_counter);

	runner_test(test_imm_operand);
	runner_test(test_imm_operand_address);
	runner_test(test_imm_address_mode);
	runner_test(test_imm_program_counter);

	runner_test(test_imp_address_mode);

	runner_test(test_zpa_operand);
	runner_test(test_zpa_operand_address);
	runner_test(test_zpa_address_mode);
	runner_test(test_zpa_program_counter);

	runner_test(test_zpx_operand);
	runner_test(test_zpx_operand_address);
	runner_test(test_zpx_address_mode);
	runner_test(test_zpx_program_counter);

	runner_test(test_zpy_operand);
	runner_test(test_zpy_operand_address);
	runner_test(test_zpy_address_mode);
	runner_test(test_zpy_program_counter);

	runner_test(test_and);
	runner_test(test_and_zero);
	runner_test(test_and_negative);

	runner_test(test_asl_memory);
	runner_test(test_asl_accumulator);
	runner_test(test_asl_carry);
	runner_test(test_asl_zero);
	runner_test(test_asl_negative);

	runner_test(test_bcc_carry_yes);
	runner_test(test_bcc_carry_no);

	runner_test(test_bcs_carry_yes);
	runner_test(test_bcs_carry_no);

	runner_test(test_beq_zero_yes);
	runner_test(test_beq_zero_no);

	runner_test(test_bit_zero);
	runner_test(test_bit_overflow);
	runner_test(test_bit_negative);

	runner_test(test_bmi_negative_yes);
	runner_test(test_bmi_negative_no);

	runner_test(test_bne_zero_yes);
	runner_test(test_bne_zero_no);

	runner_test(test_bpl_negative_yes);
	runner_test(test_bpl_negative_no);

	runner_test(test_brk);
	runner_test(test_brk_status);
	runner_test(test_brk_program_counter);

	runner_test(test_bvc_overflow_yes);
	runner_test(test_bvc_overflow_no);

	runner_test(test_bvs_overflow_yes);
	runner_test(test_bvs_overflow_no);

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

	runner_test(test_iny);
	runner_test(test_iny_zero);
	runner_test(test_iny_negative);

	runner_test(test_jmp);

	runner_test(test_jsr);

	runner_test(test_lda);
	runner_test(test_lda_zero);
	runner_test(test_lda_negative);

	runner_test(test_ldx);
	runner_test(test_ldx_zero);
	runner_test(test_ldx_negative);

	runner_test(test_ldy);
	runner_test(test_ldy_zero);
	runner_test(test_ldy_negative);

	runner_test(test_lsr_memory);
	runner_test(test_lsr_accumulator);
	runner_test(test_lsr_carry);
	runner_test(test_lsr_zero);

	runner_test(test_nop);

	runner_test(test_ora);
	runner_test(test_ora_zero);
	runner_test(test_ora_negative);

	runner_test(test_pha);

	runner_test(test_php_carry);
	runner_test(test_php_zero);
	runner_test(test_php_interrupt_disable);
	runner_test(test_php_decimal_mode);
	runner_test(test_php_overflow);
	runner_test(test_php_negative);

	runner_test(test_pla);
	runner_test(test_pla_zero);
	runner_test(test_pla_negative);

	runner_test(test_plp_carry);
	runner_test(test_plp_zero);
	runner_test(test_plp_interrupt_disable);
	runner_test(test_plp_decimal_mode);
	runner_test(test_plp_overflow);
	runner_test(test_plp_negative);

	runner_test(test_rol_memory);
	runner_test(test_rol_accumulator);
	runner_test(test_rol_carry);
	runner_test(test_rol_zero);
	runner_test(test_rol_negative);

	runner_test(test_ror_memory);
	runner_test(test_ror_accumulator);
	runner_test(test_ror_carry);
	runner_test(test_ror_zero);

	runner_test(test_rti);

	runner_test(test_rts);

	runner_test(test_sec);

	runner_test(test_sed);

	runner_test(test_sei);

	runner_test(test_sta);

	runner_test(test_stx);

	runner_test(test_sty);

	runner_test(test_tax);
	runner_test(test_tax_zero);
	runner_test(test_tax_negative);

	runner_test(test_tay);
	runner_test(test_tay_zero);
	runner_test(test_tay_negative);

	runner_test(test_tsx);
	runner_test(test_tsx_zero);
	runner_test(test_tsx_negative);

	runner_test(test_txa);
	runner_test(test_txa_zero);
	runner_test(test_txa_negative);

	runner_test(test_txs);
	runner_test(test_txs_zero);
	runner_test(test_txs_negative);

	runner_test(test_tya);
	runner_test(test_tya_zero);
	runner_test(test_tya_negative);

	return runner_report();
}