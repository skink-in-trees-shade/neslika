#include "addressing/abo.h"
#include "addressing/abx.h"
#include "addressing/aby.h"
#include "addressing/acc.h"
#include "addressing/iix.h"
#include "addressing/iiy.h"
#include "addressing/imm.h"
#include "addressing/imp.h"
#include "addressing/ind.h"
#include "addressing/rel.h"
#include "addressing/zpa.h"
#include "addressing/zpx.h"
#include "addressing/zpy.h"
#include "addressing_table.h"

addressing_fn addressing_table[0x100] = {
/*          0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F */
/* 0x00 */  imp,  iix,  NULL, NULL, NULL, zpa,  zpa,  NULL, imp,  imm,  acc,  NULL, NULL, abo,  abo,  NULL,
/* 0x10 */  rel,  iiy,  NULL, NULL, NULL, zpx,  zpx,  NULL, imp,  aby,  NULL, NULL, NULL, abx,  abx,  NULL,
/* 0x20 */  abo,  iix,  NULL, iix,  zpa,  zpa,  zpa,  zpa,  imp,  imm,  acc,  NULL, abo,  abo,  abo,  abo,
/* 0x30 */  rel,  iiy,  NULL, iiy,  NULL, zpx,  zpx,  zpx,  imp,  aby,  NULL, aby,  NULL, abx,  abx,  abx,
/* 0x40 */  imp,  iix,  NULL, NULL, NULL, zpa,  zpa,  NULL, imp,  imm,  acc,  NULL, abo,  abo,  abo,  NULL,
/* 0x50 */  rel,  iiy,  NULL, NULL, NULL, zpx,  zpx,  NULL, imp,  aby,  NULL, NULL, NULL, abx,  abx,  NULL,
/* 0x60 */  imp,  iix,  NULL, NULL, NULL, zpa,  zpa,  NULL, imp,  imm,  acc,  NULL, ind,  abo,  abo,  NULL,
/* 0x70 */  rel,  iiy,  NULL, NULL, NULL, zpx,  zpx,  NULL, imp,  aby,  NULL, NULL, NULL, abx,  abx,  NULL,
/* 0x80 */  NULL, iix,  NULL, NULL, zpa,  zpa,  zpa,  NULL, imp,  NULL, imp,  NULL, abo,  abo,  abo,  NULL,
/* 0x90 */  rel,  iiy,  NULL, NULL, zpx,  zpx,  zpy,  NULL, imp,  aby,  imp,  NULL, NULL, abx,  NULL, NULL,
/* 0xA0 */  imm,  iix,  imm,  iix,  zpa,  zpa,  zpa,  zpa,  imp,  imm,  imp,  NULL, abo,  abo,  abo,  abo,
/* 0xB0 */  rel,  iiy,  NULL, iiy,  zpx,  zpx,  zpy,  zpy,  imp,  aby,  imp,  NULL, abx,  abx,  aby,  aby,
/* 0xC0 */  imm,  iix,  NULL, iix,  zpa,  zpa,  zpa,  zpa,  imp,  imm,  imp,  NULL, abo,  abo,  abo,  abo,
/* 0xD0 */  rel,  iiy,  NULL, iiy,  NULL, zpx,  zpx,  zpx,  imp,  aby,  NULL, aby,  NULL, abx,  abx,  abx,
/* 0xE0 */  imm,  iix,  NULL, iix,  zpa,  zpa,  zpa,  zpa,  imp,  imm,  imp,  NULL, abo,  abo,  abo,  abo,
/* 0xF0 */  rel,  iiy,  NULL, iiy,  NULL, zpx,  zpx,  zpx,  imp,  aby,  NULL, aby,  NULL, abx,  abx,  abx
};