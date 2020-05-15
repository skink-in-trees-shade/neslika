#include "instruction/adc.h"
#include "instruction/and.h"
#include "instruction/asl.h"
#include "instruction/bcc.h"
#include "instruction/bcs.h"
#include "instruction/beq.h"
#include "instruction/bit.h"
#include "instruction/bmi.h"
#include "instruction/bne.h"
#include "instruction/bpl.h"
#include "instruction/brk.h"
#include "instruction/bvc.h"
#include "instruction/bvs.h"
#include "instruction/clc.h"
#include "instruction/cld.h"
#include "instruction/cli.h"
#include "instruction/clv.h"
#include "instruction/cmp.h"
#include "instruction/cpx.h"
#include "instruction/cpy.h"
#include "instruction/dcp.h"
#include "instruction/dec.h"
#include "instruction/dex.h"
#include "instruction/dey.h"
#include "instruction/eor.h"
#include "instruction/inc.h"
#include "instruction/inx.h"
#include "instruction/iny.h"
#include "instruction/isc.h"
#include "instruction/jmp.h"
#include "instruction/jsr.h"
#include "instruction/lax.h"
#include "instruction/lda.h"
#include "instruction/ldx.h"
#include "instruction/ldy.h"
#include "instruction/lsr.h"
#include "instruction/nop.h"
#include "instruction/ora.h"
#include "instruction/pha.h"
#include "instruction/php.h"
#include "instruction/pla.h"
#include "instruction/plp.h"
#include "instruction/rla.h"
#include "instruction/rol.h"
#include "instruction/ror.h"
#include "instruction/rra.h"
#include "instruction/rti.h"
#include "instruction/rts.h"
#include "instruction/sax.h"
#include "instruction/sbc.h"
#include "instruction/sec.h"
#include "instruction/sed.h"
#include "instruction/sei.h"
#include "instruction/slo.h"
#include "instruction/sre.h"
#include "instruction/sta.h"
#include "instruction/stx.h"
#include "instruction/sty.h"
#include "instruction/tax.h"
#include "instruction/tay.h"
#include "instruction/tsx.h"
#include "instruction/txa.h"
#include "instruction/txs.h"
#include "instruction/tya.h"
#include "instruction_table.h"

instruction_fn instruction_table[0x100] = {
/*          0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
/* 0x00 */  brk,  ora,  NULL, slo,  NULL, ora,  asl,  slo,  php,  ora,  asl,  NULL, NULL, ora,  asl,  slo,
/* 0x10 */  bpl,  ora,  NULL, slo,  NULL, ora,  asl,  slo,  clc,  ora,  NULL, slo,  NULL, ora,  asl,  slo,
/* 0x20 */  jsr,  and,  NULL, rla,  bit,  and,  rol,  rla,  plp,  and,  rol,  NULL, bit,  and,  rol,  rla,
/* 0x30 */  bmi,  and,  NULL, rla,  NULL, and,  rol,  rla,  sec,  and,  NULL, rla,  NULL, and,  rol,  rla,
/* 0x40 */  rti,  eor,  NULL, sre,  NULL, eor,  lsr,  sre,  pha,  eor,  lsr,  NULL, jmp,  eor,  lsr,  sre,
/* 0x50 */  bvc,  eor,  NULL, sre,  NULL, eor,  lsr,  sre,  cli,  eor,  NULL, sre,  NULL, eor,  lsr,  sre,
/* 0x60 */  rts,  adc,  NULL, rra,  NULL, adc,  ror,  rra,  pla,  adc,  ror,  NULL, jmp,  adc,  ror,  rra,
/* 0x70 */  bvs,  adc,  NULL, rra,  NULL, adc,  ror,  rra,  sei,  adc,  NULL, rra,  NULL, adc,  ror,  rra,
/* 0x80 */  NULL, sta,  NULL, sax,  sty,  sta,  stx,  sax,  dey,  NULL, txa,  NULL, sty,  sta,  stx,  sax,
/* 0x90 */  bcc,  sta,  NULL, NULL, sty,  sta,  stx,  sax,  tya,  sta,  txs,  NULL, NULL, sta,  NULL, NULL,
/* 0xA0 */  ldy,  lda,  ldx,  lax,  ldy,  lda,  ldx,  lax,  tay,  lda,  tax,  NULL, ldy,  lda,  ldx,  lax,
/* 0xB0 */  bcs,  lda,  NULL, lax,  ldy,  lda,  ldx,  lax,  clv,  lda,  tsx,  NULL, ldy,  lda,  ldx,  lax,
/* 0xC0 */  cpy,  cmp,  NULL, dcp,  cpy,  cmp,  dec,  dcp,  iny,  cmp,  dex,  NULL, cpy,  cmp,  dec,  dcp,
/* 0xD0 */  bne,  cmp,  NULL, dcp,  NULL, cmp,  dec,  dcp,  cld,  cmp,  NULL, dcp,  NULL, cmp,  dec,  dcp,
/* 0xE0 */  cpx,  sbc,  NULL, isc,  cpx,  sbc,  inc,  isc,  inx,  sbc,  nop,  NULL, cpx,  sbc,  inc,  isc,
/* 0xF0 */  beq,  sbc,  NULL, isc,  NULL, sbc,  inc,  isc,  sed,  sbc,  NULL, isc,  NULL, sbc,  inc,  isc
};