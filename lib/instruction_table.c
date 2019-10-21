#include "instruction/and.h"
#include "instruction/brk.h"
#include "instruction/clc.h"
#include "instruction/cld.h"
#include "instruction/cli.h"
#include "instruction/clv.h"
#include "instruction/cmp.h"
#include "instruction/cpx.h"
#include "instruction/cpy.h"
#include "instruction/dec.h"
#include "instruction/dex.h"
#include "instruction/dey.h"
#include "instruction/eor.h"
#include "instruction/inc.h"
#include "instruction/inx.h"
#include "instruction/iny.h"
#include "instruction/lda.h"
#include "instruction/ldx.h"
#include "instruction/ldy.h"
#include "instruction/nop.h"
#include "instruction/ora.h"
#include "instruction/sec.h"
#include "instruction/sed.h"
#include "instruction/sei.h"
#include "instruction/tax.h"
#include "instruction/tay.h"
#include "instruction/txa.h"
#include "instruction/tya.h"
#include "instruction_table.h"

instruction_t instruction_table[0x100] = {
/*          0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
/* 0x00 */  brk,  ora,  NULL, NULL, NULL, ora,  NULL, NULL, NULL, ora,  NULL, NULL, NULL, ora,  NULL, NULL,
/* 0x10 */  NULL, ora,  NULL, NULL, NULL, ora,  NULL, NULL, clc,  ora,  NULL, NULL, NULL, ora,  NULL, NULL,
/* 0x20 */  NULL, and,  NULL, NULL, NULL, and,  NULL, NULL, NULL, and,  NULL, NULL, NULL, and,  NULL, NULL,
/* 0x30 */  NULL, and,  NULL, NULL, NULL, and,  NULL, NULL, sec,  and,  NULL, NULL, NULL, and,  NULL, NULL,
/* 0x40 */  NULL, eor,  NULL, NULL, NULL, eor,  NULL, NULL, NULL, eor,  NULL, NULL, NULL, eor,  NULL, NULL,
/* 0x50 */  NULL, eor,  NULL, NULL, NULL, eor,  NULL, NULL, cli,  eor,  NULL, NULL, NULL, eor,  NULL, NULL,
/* 0x60 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x70 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, sei,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x80 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, dey,  NULL, txa,  NULL, NULL, NULL, NULL, NULL,
/* 0x90 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, tya,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xA0 */  ldy,  lda,  ldx,  NULL, ldy,  lda,  ldx,  NULL, tay,  lda,  tax,  NULL, ldy,  lda,  ldx,  NULL,
/* 0xB0 */  NULL, lda,  NULL, NULL, ldy,  lda,  ldx,  NULL, clv,  lda,  NULL, NULL, ldy,  lda,  ldx,  NULL,
/* 0xC0 */  cpy,  cmp,  NULL, NULL, cpy,  cmp,  dec,  NULL, iny,  cmp,  dex,  NULL, cpy,  cmp,  dec,  NULL,
/* 0xD0 */  NULL, cmp,  NULL, NULL, NULL, cmp,  dec,  NULL, cld,  cmp,  NULL, NULL, NULL, cmp,  dec,  NULL,
/* 0xE0 */  cpx,  NULL, NULL, NULL, cpx,  NULL, inc,  NULL, inx,  NULL, nop,  NULL, cpx,  NULL, inc,  NULL,
/* 0xF0 */  NULL, NULL, NULL, NULL, NULL, NULL, inc,  NULL, sed,  NULL, NULL, NULL, NULL, NULL, inc,  NULL
};