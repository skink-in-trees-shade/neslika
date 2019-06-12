#include <stddef.h>
#include "addressing/implicit.h"
#include "addressing/immediate.h"
#include "addressing/zero_page.h"
#include "addressing/zero_page_x.h"
#include "addressing/zero_page_y.h"
#include "addressing/absolute.h"
#include "addressing/absolute_x.h"
#include "addressing/absolute_y.h"
#include "addressing/indirect_x.h"
#include "addressing/indirect_y.h"
#include "instruction/lda.h"
#include "instruction/nop.h"
#include "table.h"

opcode_t table[] = {
/* 0x00 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x04 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x08 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x0C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x10 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x14 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x18 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x1C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x20 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x24 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x28 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x2C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x30 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x34 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x38 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x3C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x40 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x44 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x48 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x4C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x50 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x54 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x58 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x5C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x60 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x64 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x68 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x6C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x70 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x74 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x78 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x7C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x80 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x84 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x88 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x8C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x90 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x94 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x98 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0x9C */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xA0 */	{ NULL, NULL },        { indirect_x, lda },   { NULL, NULL },        { NULL, NULL },
/* 0xA4 */	{ NULL, NULL },        { zero_page, lda },    { NULL, NULL },        { NULL, NULL },
/* 0xA8 */	{ NULL, NULL },        { immediate, lda },    { NULL, NULL },        { NULL, NULL },
/* 0xAC */	{ NULL, NULL },        { absolute, lda },     { NULL, NULL },        { NULL, NULL },
/* 0xB0 */	{ NULL, NULL },        { indirect_y, lda },   { NULL, NULL },        { NULL, NULL },
/* 0xB4 */	{ NULL, NULL },        { zero_page_x, lda },  { NULL, NULL },        { NULL, NULL },
/* 0xB8 */	{ NULL, NULL },        { absolute_y, lda },   { NULL, NULL },        { NULL, NULL },
/* 0xBC */	{ NULL, NULL },        { absolute_x, lda },   { NULL, NULL },        { NULL, NULL },
/* 0xC0 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xC4 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xC8 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xCC */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xD0 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xD4 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xD8 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xDC */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xE0 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xE4 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xE8 */	{ NULL, NULL },        { NULL, NULL },        { implicit, nop },     { NULL, NULL },
/* 0xEC */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xF0 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xF4 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xF8 */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL },
/* 0xFC */	{ NULL, NULL },        { NULL, NULL },        { NULL, NULL },        { NULL, NULL }
};