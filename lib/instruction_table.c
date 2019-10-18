#include "instruction/clc.h"
#include "instruction/cld.h"
#include "instruction/cli.h"
#include "instruction/clv.h"
#include "instruction/lda.h"
#include "instruction/ldx.h"
#include "instruction/ldy.h"
#include "instruction/nop.h"
#include "instruction_table.h"

instruction_t instruction_table[0x100] = {
/*          0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
/* 0x00 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x10 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, clc,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x20 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x30 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x40 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x50 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, cli,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x60 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x70 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x80 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x90 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xA0 */  ldy,  lda,  ldx,  NULL, ldy,  lda,  ldx,  NULL, NULL, lda,  NULL, NULL, ldy,  lda,  ldx,  NULL,
/* 0xB0 */  NULL, lda,  NULL, NULL, ldy,  lda,  ldx,  NULL, clv,  lda,  NULL, NULL, ldy,  lda,  ldx,  NULL,
/* 0xC0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xD0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, cld,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xE0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, nop,  NULL, NULL, NULL, NULL, NULL,
/* 0xF0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};