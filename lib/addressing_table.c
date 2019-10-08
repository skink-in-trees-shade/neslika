#include "addressing/absolute_x.h"
#include "addressing/absolute_y.h"
#include "addressing/absolute.h"
#include "addressing/immediate.h"
#include "addressing/implicit.h"
#include "addressing/indirect_x.h"
#include "addressing/indirect_y.h"
#include "addressing/zero_page_x.h"
#include "addressing/zero_page_y.h"
#include "addressing/zero_page.h"
#include "addressing_table.h"

addressing_t addressing_table[0x100] = {
/*          0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
/* 0x00 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x10 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x20 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x30 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x40 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x50 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x60 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x70 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x80 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0x90 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xA0 */  immediate, indirect_x, immediate, NULL, zero_page, zero_page, zero_page, NULL, NULL, immediate, NULL, NULL, absolute, absolute, absolute, NULL,
/* 0xB0 */  NULL, indirect_y, NULL, NULL, zero_page_x, zero_page_x, zero_page_y, NULL, NULL, absolute_y, NULL, NULL, absolute_x, absolute_x, absolute_y, NULL,
/* 0xC0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xD0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
/* 0xE0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, implicit, NULL, NULL, NULL, NULL, NULL,
/* 0xF0 */  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};