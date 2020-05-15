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
#include "instruction.h"

struct instruction instructions[0x100] = {
/* 0x00 */ { "BRK", 0,  brk,  imp },
/* 0x01 */ { "ORA", 0,  ora,  iix },
/* 0x02 */ {  NULL, 0, NULL, NULL },
/* 0x03 */ { "SLO", 1,  slo,  iix },
/* 0x04 */ {  NULL, 0, NULL, NULL },
/* 0x05 */ { "ORA", 0,  ora,  zpa },
/* 0x06 */ { "ASL", 0,  asl,  zpa },
/* 0x07 */ { "SLO", 1,  slo,  zpa },
/* 0x08 */ { "PHP", 0,  php,  imp },
/* 0x09 */ { "ORA", 0,  ora,  imm },
/* 0x0A */ { "ASL", 0,  asl,  acc },
/* 0x0B */ {  NULL, 0, NULL, NULL },
/* 0x0C */ {  NULL, 0, NULL, NULL },
/* 0x0D */ { "ORA", 0,  ora,  abo },
/* 0x0E */ { "ASL", 0,  asl,  abo },
/* 0x0F */ { "SLO", 1,  slo,  abo },
/* 0x10 */ { "BPL", 0,  bpl,  rel },
/* 0x11 */ { "ORA", 0,  ora,  iiy },
/* 0x12 */ {  NULL, 0, NULL, NULL },
/* 0x13 */ { "SLO", 1,  slo,  iiy },
/* 0x14 */ {  NULL, 0, NULL, NULL },
/* 0x15 */ { "ORA", 0,  ora,  zpx },
/* 0x16 */ { "ASL", 0,  asl,  zpx },
/* 0x17 */ { "SLO", 1,  slo,  zpx },
/* 0x18 */ { "CLC", 0,  clc,  imp },
/* 0x19 */ { "ORA", 0,  ora,  aby },
/* 0x1A */ {  NULL, 0, NULL, NULL },
/* 0x1B */ { "SLO", 1,  slo,  aby },
/* 0x1C */ {  NULL, 0, NULL, NULL },
/* 0x1D */ { "ORA", 0,  ora,  abx },
/* 0x1E */ { "ASL", 0,  asl,  abx },
/* 0x1F */ { "SLO", 1,  slo,  abx },
/* 0x20 */ { "JSR", 0,  jsr,  abo },
/* 0x21 */ { "AND", 0,  and,  iix },
/* 0x22 */ {  NULL, 0, NULL, NULL },
/* 0x23 */ { "RLA", 1,  rla,  iix },
/* 0x24 */ { "BIT", 0,  bit,  zpa },
/* 0x25 */ { "AND", 0,  and,  zpa },
/* 0x26 */ { "ROL", 0,  rol,  zpa },
/* 0x27 */ { "RLA", 1,  rla,  zpa },
/* 0x28 */ { "PLP", 0,  plp,  imp },
/* 0x29 */ { "AND", 0,  and,  imm },
/* 0x2A */ { "ROL", 0,  rol,  acc },
/* 0x2B */ {  NULL, 0, NULL, NULL },
/* 0x2C */ { "BIT", 0,  bit,  abo },
/* 0x2D */ { "AND", 0,  and,  abo },
/* 0x2E */ { "ROL", 0,  rol,  abo },
/* 0x2F */ { "RLA", 1,  rla,  abo },
/* 0x30 */ { "BMI", 0,  bmi,  rel },
/* 0x31 */ { "AND", 0,  and,  iiy },
/* 0x32 */ {  NULL, 0, NULL, NULL },
/* 0x33 */ { "RLA", 1,  rla,  iiy },
/* 0x34 */ {  NULL, 0, NULL, NULL },
/* 0x35 */ { "AND", 0,  and,  zpx },
/* 0x36 */ { "ROL", 0,  rol,  zpx },
/* 0x37 */ { "RLA", 1,  rla,  zpx },
/* 0x38 */ { "SEC", 0,  sec,  imp },
/* 0x39 */ { "AND", 0,  and,  aby },
/* 0x3A */ {  NULL, 0, NULL, NULL },
/* 0x3B */ { "RLA", 1,  rla,  aby },
/* 0x3C */ {  NULL, 0, NULL, NULL },
/* 0x3D */ { "AND", 0,  and,  abx },
/* 0x3E */ { "ROL", 0,  rol,  abx },
/* 0x3F */ { "RLA", 1,  rla,  abx },
/* 0x40 */ { "RTI", 0,  rti,  imp },
/* 0x41 */ { "EOR", 0,  eor,  iix },
/* 0x42 */ {  NULL, 0, NULL, NULL },
/* 0x43 */ { "SRE", 1,  sre,  iix },
/* 0x44 */ {  NULL, 0, NULL, NULL },
/* 0x45 */ { "EOR", 0,  eor,  zpa },
/* 0x46 */ { "LSR", 0,  lsr,  zpa },
/* 0x47 */ { "SRE", 1,  sre,  zpa },
/* 0x48 */ { "PHA", 0,  pha,  imp },
/* 0x49 */ { "EOR", 0,  eor,  imm },
/* 0x4A */ { "LSR", 0,  lsr,  acc },
/* 0x4B */ {  NULL, 0, NULL, NULL },
/* 0x4C */ { "JMP", 0,  jmp,  abo },
/* 0x4D */ { "EOR", 0,  eor,  abo },
/* 0x4E */ { "LSR", 0,  lsr,  abo },
/* 0x4F */ { "SRE", 1,  sre,  abo },
/* 0x50 */ { "BVC", 0,  bvc,  rel },
/* 0x51 */ { "EOR", 0,  eor,  iiy },
/* 0x52 */ {  NULL, 0, NULL, NULL },
/* 0x53 */ { "SRE", 1,  sre,  iiy },
/* 0x54 */ {  NULL, 0, NULL, NULL },
/* 0x55 */ { "EOR", 0,  eor,  zpx },
/* 0x56 */ { "LSR", 0,  lsr,  zpx },
/* 0x57 */ { "SRE", 1,  sre,  zpx },
/* 0x58 */ { "CLI", 0,  cli,  imp },
/* 0x59 */ { "EOR", 0,  eor,  aby },
/* 0x5A */ {  NULL, 0, NULL, NULL },
/* 0x5B */ { "SRE", 1,  sre,  aby },
/* 0x5C */ {  NULL, 0, NULL, NULL },
/* 0x5D */ { "EOR", 0,  eor,  abx },
/* 0x5E */ { "LSR", 0,  lsr,  abx },
/* 0x5F */ { "SRE", 1,  sre,  abx },
/* 0x60 */ { "RTS", 0,  rts,  imp },
/* 0x61 */ { "ADC", 0,  adc,  iix },
/* 0x62 */ {  NULL, 0, NULL, NULL },
/* 0x63 */ { "RRA", 1,  rra,  iix },
/* 0x64 */ {  NULL, 0, NULL, NULL },
/* 0x65 */ { "ADC", 0,  adc,  zpa },
/* 0x66 */ { "ROR", 0,  ror,  zpa },
/* 0x67 */ { "RRA", 1,  rra,  zpa },
/* 0x68 */ { "PLA", 0,  pla,  imp },
/* 0x69 */ { "ADC", 0,  adc,  imm },
/* 0x6A */ { "ROR", 0,  ror,  acc },
/* 0x6B */ {  NULL, 0, NULL, NULL },
/* 0x6C */ { "JMP", 0,  jmp,  ind },
/* 0x6D */ { "ADC", 0,  adc,  abo },
/* 0x6E */ { "ROR", 0,  ror,  abo },
/* 0x6F */ { "RRA", 1,  rra,  abo },
/* 0x70 */ { "BVS", 0,  bvs,  rel },
/* 0x71 */ { "ADC", 0,  adc,  iiy },
/* 0x72 */ {  NULL, 0, NULL, NULL },
/* 0x73 */ { "RRA", 1,  rra,  iiy },
/* 0x74 */ {  NULL, 0, NULL, NULL },
/* 0x75 */ { "ADC", 0,  adc,  zpx },
/* 0x76 */ { "ROR", 0,  ror,  zpx },
/* 0x77 */ { "RRA", 1,  rra,  zpx },
/* 0x78 */ { "SEI", 0,  sei,  imp },
/* 0x79 */ { "ADC", 0,  adc,  aby },
/* 0x7A */ {  NULL, 0, NULL, NULL },
/* 0x7B */ { "RRA", 1,  rra,  aby },
/* 0x7C */ {  NULL, 0, NULL, NULL },
/* 0x7D */ { "ADC", 0,  adc,  abx },
/* 0x7E */ { "ROR", 0,  ror,  abx },
/* 0x7F */ { "RRA", 1,  rra,  abx },
/* 0x80 */ {  NULL, 0, NULL, NULL },
/* 0x81 */ { "STA", 0,  sta,  iix },
/* 0x82 */ {  NULL, 0, NULL, NULL },
/* 0x83 */ { "SAX", 1,  sax,  iix },
/* 0x84 */ { "STY", 0,  sty,  zpa },
/* 0x85 */ { "STA", 0,  sta,  zpa },
/* 0x86 */ { "STX", 0,  stx,  zpa },
/* 0x87 */ { "SAX", 1,  sax,  zpa },
/* 0x88 */ { "DEY", 0,  dey,  imp },
/* 0x89 */ {  NULL, 0, NULL, NULL },
/* 0x8A */ { "TXA", 0,  txa,  imp },
/* 0x8B */ {  NULL, 0, NULL, NULL },
/* 0x8C */ { "STY", 0,  sty,  abo },
/* 0x8D */ { "STA", 0,  sta,  abo },
/* 0x8E */ { "STX", 0,  stx,  abo },
/* 0x8F */ { "SAX", 1,  sax,  abo },
/* 0x90 */ { "BCC", 0,  bcc,  rel },
/* 0x91 */ { "STA", 0,  sta,  iiy },
/* 0x92 */ {  NULL, 0, NULL, NULL },
/* 0x93 */ {  NULL, 0, NULL, NULL },
/* 0x94 */ { "STY", 0,  sty,  zpx },
/* 0x95 */ { "STA", 0,  sta,  zpx },
/* 0x96 */ { "STX", 0,  stx,  zpy },
/* 0x97 */ { "SAX", 1,  sax,  zpy },
/* 0x98 */ { "TYA", 0,  tya,  imp },
/* 0x99 */ { "STA", 0,  sta,  aby },
/* 0x9A */ { "TXS", 0,  txs,  imp },
/* 0x9B */ {  NULL, 0, NULL, NULL },
/* 0x9C */ {  NULL, 0, NULL, NULL },
/* 0x9D */ { "STA", 0,  sta,  abx },
/* 0x9E */ {  NULL, 0, NULL, NULL },
/* 0x9F */ {  NULL, 0, NULL, NULL },
/* 0xA0 */ { "LDY", 0,  ldy,  imm },
/* 0xA1 */ { "LDA", 0,  lda,  iix },
/* 0xA2 */ { "LDX", 0,  ldx,  imm },
/* 0xA3 */ { "LAX", 1,  lax,  iix },
/* 0xA4 */ { "LDY", 0,  ldy,  zpa },
/* 0xA5 */ { "LDA", 0,  lda,  zpa },
/* 0xA6 */ { "LDX", 0,  ldx,  zpa },
/* 0xA7 */ { "LAX", 1,  lax,  zpa },
/* 0xA8 */ { "TAY", 0,  tay,  imp },
/* 0xA9 */ { "LDA", 0,  lda,  imm },
/* 0xAA */ { "TAX", 0,  tax,  imp },
/* 0xAB */ {  NULL, 0, NULL, NULL },
/* 0xAC */ { "LDY", 0,  ldy,  abo },
/* 0xAD */ { "LDA", 0,  lda,  abo },
/* 0xAE */ { "LDX", 0,  ldx,  abo },
/* 0xAF */ { "LAX", 1,  lax,  abo },
/* 0xB0 */ { "BCS", 0,  bcs,  rel },
/* 0xB1 */ { "LDA", 0,  lda,  iiy },
/* 0xB2 */ {  NULL, 0, NULL, NULL },
/* 0xB3 */ { "LAX", 1,  lax,  iiy },
/* 0xB4 */ { "LDY", 0,  ldy,  zpx },
/* 0xB5 */ { "LDA", 0,  lda,  zpx },
/* 0xB6 */ { "LDX", 0,  ldx,  zpy },
/* 0xB7 */ { "LAX", 1,  lax,  zpy },
/* 0xB8 */ { "CLV", 0,  clv,  imp },
/* 0xB9 */ { "LDA", 0,  lda,  aby },
/* 0xBA */ { "TSX", 0,  tsx,  imp },
/* 0xBB */ {  NULL, 0, NULL, NULL },
/* 0xBC */ { "LDY", 0,  ldy,  abx },
/* 0xBD */ { "LDA", 0,  lda,  abx },
/* 0xBE */ { "LDX", 0,  ldx,  aby },
/* 0xBF */ { "LAX", 1,  lax,  aby },
/* 0xC0 */ { "CPY", 0,  cpy,  imm },
/* 0xC1 */ { "CMP", 0,  cmp,  iix },
/* 0xC2 */ {  NULL, 0, NULL, NULL },
/* 0xC3 */ { "DCP", 1,  dcp,  iix },
/* 0xC4 */ { "CPY", 0,  cpy,  zpa },
/* 0xC5 */ { "CMP", 0,  cmp,  zpa },
/* 0xC6 */ { "DEC", 0,  dec,  zpa },
/* 0xC7 */ { "DCP", 1,  dcp,  zpa },
/* 0xC8 */ { "INY", 0,  iny,  imp },
/* 0xC9 */ { "CMP", 0,  cmp,  imm },
/* 0xCA */ { "DEX", 0,  dex,  imp },
/* 0xCB */ {  NULL, 0, NULL, NULL },
/* 0xCC */ { "CPY", 0,  cpy,  abo },
/* 0xCD */ { "CMP", 0,  cmp,  abo },
/* 0xCE */ { "DEC", 0,  dec,  abo },
/* 0xCF */ { "DCP", 1,  dcp,  abo },
/* 0xD0 */ { "BNE", 0,  bne,  rel },
/* 0xD1 */ { "CMP", 0,  cmp,  iiy },
/* 0xD2 */ {  NULL, 0, NULL, NULL },
/* 0xD3 */ { "DCP", 1,  dcp,  iiy },
/* 0xD4 */ {  NULL, 0, NULL, NULL },
/* 0xD5 */ { "CMP", 0,  cmp,  zpx },
/* 0xD6 */ { "DEC", 0,  dec,  zpx },
/* 0xD7 */ { "DCP", 1,  dcp,  zpx },
/* 0xD8 */ { "CLD", 0,  cld,  imp },
/* 0xD9 */ { "CMP", 0,  cmp,  aby },
/* 0xDA */ {  NULL, 0, NULL, NULL },
/* 0xDB */ { "DCP", 1,  dcp,  aby },
/* 0xDC */ {  NULL, 0, NULL, NULL },
/* 0xDD */ { "CMP", 0,  cmp,  abx },
/* 0xDE */ { "DEC", 0,  dec,  abx },
/* 0xDF */ { "DCP", 1,  dcp,  abx },
/* 0xE0 */ { "CPX", 0,  cpx,  imm },
/* 0xE1 */ { "SBC", 0,  sbc,  iix },
/* 0xE2 */ {  NULL, 0, NULL, NULL },
/* 0xE3 */ { "ISC", 1,  isc,  iix },
/* 0xE4 */ { "CPX", 0,  cpx,  zpa },
/* 0xE5 */ { "SBC", 0,  sbc,  zpa },
/* 0xE6 */ { "INC", 0,  inc,  zpa },
/* 0xE7 */ { "ISC", 1,  isc,  zpa },
/* 0xE8 */ { "INX", 0,  inx,  imp },
/* 0xE9 */ { "SBC", 0,  sbc,  imm },
/* 0xEA */ { "NOP", 0,  nop,  imp },
/* 0xEB */ {  NULL, 0, NULL, NULL },
/* 0xEC */ { "CPX", 0,  cpx,  abo },
/* 0xED */ { "SBC", 0,  sbc,  abo },
/* 0xEE */ { "INC", 0,  inc,  abo },
/* 0xEF */ { "ISC", 1,  isc,  abo },
/* 0xF0 */ { "BEQ", 0,  beq,  rel },
/* 0xF1 */ { "SBC", 0,  sbc,  iiy },
/* 0xF2 */ {  NULL, 0, NULL, NULL },
/* 0xF3 */ { "ISC", 1,  isc,  iiy },
/* 0xF4 */ {  NULL, 0, NULL, NULL },
/* 0xF5 */ { "SBC", 0,  sbc,  zpx },
/* 0xF6 */ { "INC", 0,  inc,  zpx },
/* 0xF7 */ { "ISC", 1,  isc,  zpx },
/* 0xF8 */ { "SED", 0,  sed,  imp },
/* 0xF9 */ { "SBC", 0,  sbc,  aby },
/* 0xFA */ {  NULL, 0, NULL, NULL },
/* 0xFB */ { "ISC", 1,  isc,  aby },
/* 0xFC */ {  NULL, 0, NULL, NULL },
/* 0xFD */ { "SBC", 0,  sbc,  abx },
/* 0xFE */ { "INC", 0,  inc,  abx },
/* 0xFF */ { "ISC", 1,  isc,  abx }
};