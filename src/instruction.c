#include "addressing/abj.h"
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
#include "instruction/adc.h"
#include "instruction/and.h"
#include "instruction/asl.h"
#include "instruction/asla.h"
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
#include "instruction/isb.h"
#include "instruction/jmp.h"
#include "instruction/jsr.h"
#include "instruction/lax.h"
#include "instruction/lda.h"
#include "instruction/ldx.h"
#include "instruction/ldy.h"
#include "instruction/lsr.h"
#include "instruction/lsra.h"
#include "instruction/nop.h"
#include "instruction/ora.h"
#include "instruction/pha.h"
#include "instruction/php.h"
#include "instruction/pla.h"
#include "instruction/plp.h"
#include "instruction/rla.h"
#include "instruction/rol.h"
#include "instruction/rola.h"
#include "instruction/ror.h"
#include "instruction/rora.h"
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
#include "instruction.h"

struct instruction instructions[0x100] = {
/* 0x00 */ { "BRK", 0, imp,  brk },
/* 0x01 */ { "ORA", 0, iix,  ora },
/* 0x02 */ {  NULL, 0, NULL, NULL },
/* 0x03 */ { "SLO", 1, iix,  slo },
/* 0x04 */ { "NOP", 1, zpa,  nop },
/* 0x05 */ { "ORA", 0, zpa,  ora },
/* 0x06 */ { "ASL", 0, zpa,  asl },
/* 0x07 */ { "SLO", 1, zpa,  slo },
/* 0x08 */ { "PHP", 0, imp,  php },
/* 0x09 */ { "ORA", 0, imm,  ora },
/* 0x0A */ { "ASL", 0, acc,  asla },
/* 0x0B */ {  NULL, 0, NULL, NULL },
/* 0x0C */ { "NOP", 1, abo,  nop },
/* 0x0D */ { "ORA", 0, abo,  ora },
/* 0x0E */ { "ASL", 0, abo,  asl },
/* 0x0F */ { "SLO", 1, abo,  slo },
/* 0x10 */ { "BPL", 0, rel,  bpl },
/* 0x11 */ { "ORA", 0, iiy,  ora },
/* 0x12 */ {  NULL, 0, NULL, NULL },
/* 0x13 */ { "SLO", 1, iiy,  slo },
/* 0x14 */ { "NOP", 1, zpx,  nop },
/* 0x15 */ { "ORA", 0, zpx,  ora },
/* 0x16 */ { "ASL", 0, zpx,  asl },
/* 0x17 */ { "SLO", 1, zpx,  slo },
/* 0x18 */ { "CLC", 0, imp,  clc },
/* 0x19 */ { "ORA", 0, aby,  ora },
/* 0x1A */ { "NOP", 1, imp,  nop },
/* 0x1B */ { "SLO", 1, aby,  slo },
/* 0x1C */ { "NOP", 1, abx,  nop },
/* 0x1D */ { "ORA", 0, abx,  ora },
/* 0x1E */ { "ASL", 0, abx,  asl },
/* 0x1F */ { "SLO", 1, abx,  slo },
/* 0x20 */ { "JSR", 0, abj,  jsr },
/* 0x21 */ { "AND", 0, iix,  and },
/* 0x22 */ {  NULL, 0, NULL, NULL },
/* 0x23 */ { "RLA", 1, iix,  rla },
/* 0x24 */ { "BIT", 0, zpa,  bit },
/* 0x25 */ { "AND", 0, zpa,  and },
/* 0x26 */ { "ROL", 0, zpa,  rol },
/* 0x27 */ { "RLA", 1, zpa,  rla },
/* 0x28 */ { "PLP", 0, imp,  plp },
/* 0x29 */ { "AND", 0, imm,  and },
/* 0x2A */ { "ROL", 0, acc,  rola },
/* 0x2B */ {  NULL, 0, NULL, NULL },
/* 0x2C */ { "BIT", 0, abo,  bit },
/* 0x2D */ { "AND", 0, abo,  and },
/* 0x2E */ { "ROL", 0, abo,  rol },
/* 0x2F */ { "RLA", 1, abo,  rla },
/* 0x30 */ { "BMI", 0, rel,  bmi },
/* 0x31 */ { "AND", 0, iiy,  and },
/* 0x32 */ {  NULL, 0, NULL, NULL },
/* 0x33 */ { "RLA", 1, iiy,  rla },
/* 0x34 */ { "NOP", 1, zpx,  nop },
/* 0x35 */ { "AND", 0, zpx,  and },
/* 0x36 */ { "ROL", 0, zpx,  rol },
/* 0x37 */ { "RLA", 1, zpx,  rla },
/* 0x38 */ { "SEC", 0, imp,  sec },
/* 0x39 */ { "AND", 0, aby,  and },
/* 0x3A */ { "NOP", 1, imp,  nop },
/* 0x3B */ { "RLA", 1, aby,  rla },
/* 0x3C */ { "NOP", 1, abx,  nop },
/* 0x3D */ { "AND", 0, abx,  and },
/* 0x3E */ { "ROL", 0, abx,  rol },
/* 0x3F */ { "RLA", 1, abx,  rla },
/* 0x40 */ { "RTI", 0, imp,  rti },
/* 0x41 */ { "EOR", 0, iix,  eor },
/* 0x42 */ {  NULL, 0, NULL, NULL },
/* 0x43 */ { "SRE", 1, iix,  sre },
/* 0x44 */ { "NOP", 1, zpa,  nop },
/* 0x45 */ { "EOR", 0, zpa,  eor },
/* 0x46 */ { "LSR", 0, zpa,  lsr },
/* 0x47 */ { "SRE", 1, zpa,  sre },
/* 0x48 */ { "PHA", 0, imp,  pha },
/* 0x49 */ { "EOR", 0, imm,  eor },
/* 0x4A */ { "LSR", 0, acc,  lsra },
/* 0x4B */ {  NULL, 0, NULL, NULL },
/* 0x4C */ { "JMP", 0, abj,  jmp },
/* 0x4D */ { "EOR", 0, abo,  eor },
/* 0x4E */ { "LSR", 0, abo,  lsr },
/* 0x4F */ { "SRE", 1, abo,  sre },
/* 0x50 */ { "BVC", 0, rel,  bvc },
/* 0x51 */ { "EOR", 0, iiy,  eor },
/* 0x52 */ {  NULL, 0, NULL, NULL },
/* 0x53 */ { "SRE", 1, iiy,  sre },
/* 0x54 */ { "NOP", 1, zpx,  nop },
/* 0x55 */ { "EOR", 0, zpx,  eor },
/* 0x56 */ { "LSR", 0, zpx,  lsr },
/* 0x57 */ { "SRE", 1, zpx,  sre },
/* 0x58 */ { "CLI", 0, imp,  cli },
/* 0x59 */ { "EOR", 0, aby,  eor },
/* 0x5A */ { "NOP", 1, imp,  nop },
/* 0x5B */ { "SRE", 1, aby,  sre },
/* 0x5C */ { "NOP", 1, abx,  nop },
/* 0x5D */ { "EOR", 0, abx,  eor },
/* 0x5E */ { "LSR", 0, abx,  lsr },
/* 0x5F */ { "SRE", 1, abx,  sre },
/* 0x60 */ { "RTS", 0, imp,  rts },
/* 0x61 */ { "ADC", 0, iix,  adc },
/* 0x62 */ {  NULL, 0, NULL, NULL },
/* 0x63 */ { "RRA", 1, iix,  rra },
/* 0x64 */ { "NOP", 1, zpa,  nop },
/* 0x65 */ { "ADC", 0, zpa,  adc },
/* 0x66 */ { "ROR", 0, zpa,  ror },
/* 0x67 */ { "RRA", 1, zpa,  rra },
/* 0x68 */ { "PLA", 0, imp,  pla },
/* 0x69 */ { "ADC", 0, imm,  adc },
/* 0x6A */ { "ROR", 0, acc,  rora },
/* 0x6B */ {  NULL, 0, NULL, NULL },
/* 0x6C */ { "JMP", 0, ind,  jmp },
/* 0x6D */ { "ADC", 0, abo,  adc },
/* 0x6E */ { "ROR", 0, abo,  ror },
/* 0x6F */ { "RRA", 1, abo,  rra },
/* 0x70 */ { "BVS", 0, rel,  bvs },
/* 0x71 */ { "ADC", 0, iiy,  adc },
/* 0x72 */ {  NULL, 0, NULL, NULL },
/* 0x73 */ { "RRA", 1, iiy,  rra },
/* 0x74 */ { "NOP", 1, zpx,  nop },
/* 0x75 */ { "ADC", 0, zpx,  adc },
/* 0x76 */ { "ROR", 0, zpx,  ror },
/* 0x77 */ { "RRA", 1, zpx,  rra },
/* 0x78 */ { "SEI", 0, imp,  sei },
/* 0x79 */ { "ADC", 0, aby,  adc },
/* 0x7A */ { "NOP", 1, imp,  nop },
/* 0x7B */ { "RRA", 1, aby,  rra },
/* 0x7C */ { "NOP", 1, abx,  nop },
/* 0x7D */ { "ADC", 0, abx,  adc },
/* 0x7E */ { "ROR", 0, abx,  ror },
/* 0x7F */ { "RRA", 1, abx,  rra },
/* 0x80 */ { "NOP", 1, imm,  nop },
/* 0x81 */ { "STA", 0, iix,  sta },
/* 0x82 */ {  NULL, 0, NULL, NULL },
/* 0x83 */ { "SAX", 1, iix,  sax },
/* 0x84 */ { "STY", 0, zpa,  sty },
/* 0x85 */ { "STA", 0, zpa,  sta },
/* 0x86 */ { "STX", 0, zpa,  stx },
/* 0x87 */ { "SAX", 1, zpa,  sax },
/* 0x88 */ { "DEY", 0, imp,  dey },
/* 0x89 */ {  NULL, 0, NULL, NULL },
/* 0x8A */ { "TXA", 0, imp,  txa },
/* 0x8B */ {  NULL, 0, NULL, NULL },
/* 0x8C */ { "STY", 0, abo,  sty },
/* 0x8D */ { "STA", 0, abo,  sta },
/* 0x8E */ { "STX", 0, abo,  stx },
/* 0x8F */ { "SAX", 1, abo,  sax },
/* 0x90 */ { "BCC", 0, rel,  bcc },
/* 0x91 */ { "STA", 0, iiy,  sta },
/* 0x92 */ {  NULL, 0, NULL, NULL },
/* 0x93 */ {  NULL, 0, NULL, NULL },
/* 0x94 */ { "STY", 0, zpx,  sty },
/* 0x95 */ { "STA", 0, zpx,  sta },
/* 0x96 */ { "STX", 0, zpy,  stx },
/* 0x97 */ { "SAX", 1, zpy,  sax },
/* 0x98 */ { "TYA", 0, imp,  tya },
/* 0x99 */ { "STA", 0, aby,  sta },
/* 0x9A */ { "TXS", 0, imp,  txs },
/* 0x9B */ {  NULL, 0, NULL, NULL },
/* 0x9C */ {  NULL, 0, NULL, NULL },
/* 0x9D */ { "STA", 0, abx,  sta },
/* 0x9E */ {  NULL, 0, NULL, NULL },
/* 0x9F */ {  NULL, 0, NULL, NULL },
/* 0xA0 */ { "LDY", 0, imm,  ldy },
/* 0xA1 */ { "LDA", 0, iix,  lda },
/* 0xA2 */ { "LDX", 0, imm,  ldx },
/* 0xA3 */ { "LAX", 1, iix,  lax },
/* 0xA4 */ { "LDY", 0, zpa,  ldy },
/* 0xA5 */ { "LDA", 0, zpa,  lda },
/* 0xA6 */ { "LDX", 0, zpa,  ldx },
/* 0xA7 */ { "LAX", 1, zpa,  lax },
/* 0xA8 */ { "TAY", 0, imp,  tay },
/* 0xA9 */ { "LDA", 0, imm,  lda },
/* 0xAA */ { "TAX", 0, imp,  tax },
/* 0xAB */ {  NULL, 0, NULL, NULL },
/* 0xAC */ { "LDY", 0, abo,  ldy },
/* 0xAD */ { "LDA", 0, abo,  lda },
/* 0xAE */ { "LDX", 0, abo,  ldx },
/* 0xAF */ { "LAX", 1, abo,  lax },
/* 0xB0 */ { "BCS", 0, rel,  bcs },
/* 0xB1 */ { "LDA", 0, iiy,  lda },
/* 0xB2 */ {  NULL, 0, NULL, NULL },
/* 0xB3 */ { "LAX", 1, iiy,  lax },
/* 0xB4 */ { "LDY", 0, zpx,  ldy },
/* 0xB5 */ { "LDA", 0, zpx,  lda },
/* 0xB6 */ { "LDX", 0, zpy,  ldx },
/* 0xB7 */ { "LAX", 1, zpy,  lax },
/* 0xB8 */ { "CLV", 0, imp,  clv },
/* 0xB9 */ { "LDA", 0, aby,  lda },
/* 0xBA */ { "TSX", 0, imp,  tsx },
/* 0xBB */ {  NULL, 0, NULL, NULL },
/* 0xBC */ { "LDY", 0, abx,  ldy },
/* 0xBD */ { "LDA", 0, abx,  lda },
/* 0xBE */ { "LDX", 0, aby,  ldx },
/* 0xBF */ { "LAX", 1, aby,  lax },
/* 0xC0 */ { "CPY", 0, imm,  cpy },
/* 0xC1 */ { "CMP", 0, iix,  cmp },
/* 0xC2 */ {  NULL, 0, NULL, NULL },
/* 0xC3 */ { "DCP", 1, iix,  dcp },
/* 0xC4 */ { "CPY", 0, zpa,  cpy },
/* 0xC5 */ { "CMP", 0, zpa,  cmp },
/* 0xC6 */ { "DEC", 0, zpa,  dec },
/* 0xC7 */ { "DCP", 1, zpa,  dcp },
/* 0xC8 */ { "INY", 0, imp,  iny },
/* 0xC9 */ { "CMP", 0, imm,  cmp },
/* 0xCA */ { "DEX", 0, imp,  dex },
/* 0xCB */ {  NULL, 0, NULL, NULL },
/* 0xCC */ { "CPY", 0, abo,  cpy },
/* 0xCD */ { "CMP", 0, abo,  cmp },
/* 0xCE */ { "DEC", 0, abo,  dec },
/* 0xCF */ { "DCP", 1, abo,  dcp },
/* 0xD0 */ { "BNE", 0, rel,  bne },
/* 0xD1 */ { "CMP", 0, iiy,  cmp },
/* 0xD2 */ {  NULL, 0, NULL, NULL },
/* 0xD3 */ { "DCP", 1, iiy,  dcp },
/* 0xD4 */ { "NOP", 1, zpx,  nop },
/* 0xD5 */ { "CMP", 0, zpx,  cmp },
/* 0xD6 */ { "DEC", 0, zpx,  dec },
/* 0xD7 */ { "DCP", 1, zpx,  dcp },
/* 0xD8 */ { "CLD", 0, imp,  cld },
/* 0xD9 */ { "CMP", 0, aby,  cmp },
/* 0xDA */ { "NOP", 1, imp,  nop },
/* 0xDB */ { "DCP", 1, aby,  dcp },
/* 0xDC */ { "NOP", 1, abx,  nop },
/* 0xDD */ { "CMP", 0, abx,  cmp },
/* 0xDE */ { "DEC", 0, abx,  dec },
/* 0xDF */ { "DCP", 1, abx,  dcp },
/* 0xE0 */ { "CPX", 0, imm,  cpx },
/* 0xE1 */ { "SBC", 0, iix,  sbc },
/* 0xE2 */ {  NULL, 0, NULL, NULL },
/* 0xE3 */ { "ISB", 1, iix,  isb },
/* 0xE4 */ { "CPX", 0, zpa,  cpx },
/* 0xE5 */ { "SBC", 0, zpa,  sbc },
/* 0xE6 */ { "INC", 0, zpa,  inc },
/* 0xE7 */ { "ISB", 1, zpa,  isb },
/* 0xE8 */ { "INX", 0, imp,  inx },
/* 0xE9 */ { "SBC", 0, imm,  sbc },
/* 0xEA */ { "NOP", 0, imp,  nop },
/* 0xEB */ { "SBC", 1, imm,  sbc },
/* 0xEC */ { "CPX", 0, abo,  cpx },
/* 0xED */ { "SBC", 0, abo,  sbc },
/* 0xEE */ { "INC", 0, abo,  inc },
/* 0xEF */ { "ISB", 1, abo,  isb },
/* 0xF0 */ { "BEQ", 0, rel,  beq },
/* 0xF1 */ { "SBC", 0, iiy,  sbc },
/* 0xF2 */ {  NULL, 0, NULL, NULL },
/* 0xF3 */ { "ISB", 1, iiy,  isb },
/* 0xF4 */ { "NOP", 1, zpx,  nop },
/* 0xF5 */ { "SBC", 0, zpx,  sbc },
/* 0xF6 */ { "INC", 0, zpx,  inc },
/* 0xF7 */ { "ISB", 1, zpx,  isb },
/* 0xF8 */ { "SED", 0, imp,  sed },
/* 0xF9 */ { "SBC", 0, aby,  sbc },
/* 0xFA */ { "NOP", 1, imp,  nop },
/* 0xFB */ { "ISB", 1, aby,  isb },
/* 0xFC */ { "NOP", 1, abx,  nop },
/* 0xFD */ { "SBC", 0, abx,  sbc },
/* 0xFE */ { "INC", 0, abx,  inc },
/* 0xFF */ { "ISB", 1, abx,  isb }
};