#include "addressing/abo.h"
#include "addressing/abx.h"
#include "addressing/aby.h"
#include "addressing/imm.h"
#include "addressing/imp.h"
#include "addressing/inx.h"
#include "addressing/iny.h"
#include "addressing/zpa.h"
#include "addressing/zpx.h"
#include "addressing/zpy.h"
#include "addressing_table.h"

addressing_t addressing_table[0x100] = {
/*          0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
/* 0x00 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x10 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, imp,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x20 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x30 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, imp,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x40 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x50 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, imp,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x60 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x70 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x80 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x90 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xA0 */  imm,  inx,  imm,  NULL, zpa,  zpa,  zpa,  NULL, NULL, imm,  NULL, NULL, abo,  abo,  abo,  NULL,
/* 0xB0 */  NULL, iny,  NULL, NULL, zpx,  zpx,  zpy,  NULL, imp,  aby,  NULL, NULL, abx,  abx,  aby,  NULL,
/* 0xC0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xD0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, imp,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xE0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, imp,  NULL, NULL, NULL, NULL, NULL,
/* 0xF0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, imp,  NULL, NULL, NULL, NULL, NULL, NULL, NULL
};