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
#include "instruction/alr.h"
#include "instruction/anc.h"
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
/* 0x00 */ { "BRK", 0, imp,  brk, 7 },
/* 0x01 */ { "ORA", 0, iix,  ora, 6 },
/* 0x02 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x03 */ { "SLO", 1, iix,  slo, 8 },
/* 0x04 */ { "NOP", 1, zpa,  nop, 3 },
/* 0x05 */ { "ORA", 0, zpa,  ora, 3 },
/* 0x06 */ { "ASL", 0, zpa,  asl, 5 },
/* 0x07 */ { "SLO", 1, zpa,  slo, 5 },
/* 0x08 */ { "PHP", 0, imp,  php, 3 },
/* 0x09 */ { "ORA", 0, imm,  ora, 2 },
/* 0x0A */ { "ASL", 0, acc,  asla, 2 },
/* 0x0B */ { "ANC", 1, imm,  anc, 2 },
/* 0x0C */ { "NOP", 1, abo,  nop, 4 },
/* 0x0D */ { "ORA", 0, abo,  ora, 4 },
/* 0x0E */ { "ASL", 0, abo,  asl, 6 },
/* 0x0F */ { "SLO", 1, abo,  slo, 6 },
/* 0x10 */ { "BPL", 0, rel,  bpl, 2 },
/* 0x11 */ { "ORA", 0, iiy,  ora, 5 },
/* 0x12 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x13 */ { "SLO", 1, iiy,  slo, 8 },
/* 0x14 */ { "NOP", 1, zpx,  nop, 4 },
/* 0x15 */ { "ORA", 0, zpx,  ora, 4 },
/* 0x16 */ { "ASL", 0, zpx,  asl, 6 },
/* 0x17 */ { "SLO", 1, zpx,  slo, 6 },
/* 0x18 */ { "CLC", 0, imp,  clc, 2 },
/* 0x19 */ { "ORA", 0, aby,  ora, 4 },
/* 0x1A */ { "NOP", 1, imp,  nop, 2 },
/* 0x1B */ { "SLO", 1, aby,  slo, 7 },
/* 0x1C */ { "NOP", 1, abx,  nop, 4 },
/* 0x1D */ { "ORA", 0, abx,  ora, 4 },
/* 0x1E */ { "ASL", 0, abx,  asl, 7 },
/* 0x1F */ { "SLO", 1, abx,  slo, 7 },
/* 0x20 */ { "JSR", 0, abj,  jsr, 6 },
/* 0x21 */ { "AND", 0, iix,  and, 6 },
/* 0x22 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x23 */ { "RLA", 1, iix,  rla, 8 },
/* 0x24 */ { "BIT", 0, zpa,  bit, 3 },
/* 0x25 */ { "AND", 0, zpa,  and, 3 },
/* 0x26 */ { "ROL", 0, zpa,  rol, 5 },
/* 0x27 */ { "RLA", 1, zpa,  rla, 5 },
/* 0x28 */ { "PLP", 0, imp,  plp, 4 },
/* 0x29 */ { "AND", 0, imm,  and, 2 },
/* 0x2A */ { "ROL", 0, acc,  rola, 2 },
/* 0x2B */ { "ANC", 1, imm,  anc, 2 },
/* 0x2C */ { "BIT", 0, abo,  bit, 4 },
/* 0x2D */ { "AND", 0, abo,  and, 4 },
/* 0x2E */ { "ROL", 0, abo,  rol, 6 },
/* 0x2F */ { "RLA", 1, abo,  rla, 6 },
/* 0x30 */ { "BMI", 0, rel,  bmi, 2 },
/* 0x31 */ { "AND", 0, iiy,  and, 5 },
/* 0x32 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x33 */ { "RLA", 1, iiy,  rla, 8 },
/* 0x34 */ { "NOP", 1, zpx,  nop, 4 },
/* 0x35 */ { "AND", 0, zpx,  and, 4 },
/* 0x36 */ { "ROL", 0, zpx,  rol, 6 },
/* 0x37 */ { "RLA", 1, zpx,  rla, 6 },
/* 0x38 */ { "SEC", 0, imp,  sec, 2 },
/* 0x39 */ { "AND", 0, aby,  and, 4 },
/* 0x3A */ { "NOP", 1, imp,  nop, 2 },
/* 0x3B */ { "RLA", 1, aby,  rla, 7 },
/* 0x3C */ { "NOP", 1, abx,  nop, 4 },
/* 0x3D */ { "AND", 0, abx,  and, 4 },
/* 0x3E */ { "ROL", 0, abx,  rol, 7 },
/* 0x3F */ { "RLA", 1, abx,  rla, 7 },
/* 0x40 */ { "RTI", 0, imp,  rti, 6 },
/* 0x41 */ { "EOR", 0, iix,  eor, 6 },
/* 0x42 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x43 */ { "SRE", 1, iix,  sre, 8 },
/* 0x44 */ { "NOP", 1, zpa,  nop, 3 },
/* 0x45 */ { "EOR", 0, zpa,  eor, 3 },
/* 0x46 */ { "LSR", 0, zpa,  lsr, 5 },
/* 0x47 */ { "SRE", 1, zpa,  sre, 5 },
/* 0x48 */ { "PHA", 0, imp,  pha, 3 },
/* 0x49 */ { "EOR", 0, imm,  eor, 2 },
/* 0x4A */ { "LSR", 0, acc,  lsra, 2 },
/* 0x4B */ { "ALR", 1, imm,  alr, 2 },
/* 0x4C */ { "JMP", 0, abj,  jmp, 3 },
/* 0x4D */ { "EOR", 0, abo,  eor, 4 },
/* 0x4E */ { "LSR", 0, abo,  lsr, 6 },
/* 0x4F */ { "SRE", 1, abo,  sre, 6 },
/* 0x50 */ { "BVC", 0, rel,  bvc, 2 },
/* 0x51 */ { "EOR", 0, iiy,  eor, 5 },
/* 0x52 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x53 */ { "SRE", 1, iiy,  sre, 8 },
/* 0x54 */ { "NOP", 1, zpx,  nop, 4 },
/* 0x55 */ { "EOR", 0, zpx,  eor, 4 },
/* 0x56 */ { "LSR", 0, zpx,  lsr, 6 },
/* 0x57 */ { "SRE", 1, zpx,  sre, 6 },
/* 0x58 */ { "CLI", 0, imp,  cli, 2 },
/* 0x59 */ { "EOR", 0, aby,  eor, 4 },
/* 0x5A */ { "NOP", 1, imp,  nop, 2 },
/* 0x5B */ { "SRE", 1, aby,  sre, 7 },
/* 0x5C */ { "NOP", 1, abx,  nop, 4 },
/* 0x5D */ { "EOR", 0, abx,  eor, 4 },
/* 0x5E */ { "LSR", 0, abx,  lsr, 7 },
/* 0x5F */ { "SRE", 1, abx,  sre, 7 },
/* 0x60 */ { "RTS", 0, imp,  rts, 6 },
/* 0x61 */ { "ADC", 0, iix,  adc, 6 },
/* 0x62 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x63 */ { "RRA", 1, iix,  rra, 8 },
/* 0x64 */ { "NOP", 1, zpa,  nop, 3 },
/* 0x65 */ { "ADC", 0, zpa,  adc, 3 },
/* 0x66 */ { "ROR", 0, zpa,  ror, 5 },
/* 0x67 */ { "RRA", 1, zpa,  rra, 5 },
/* 0x68 */ { "PLA", 0, imp,  pla, 4 },
/* 0x69 */ { "ADC", 0, imm,  adc, 2 },
/* 0x6A */ { "ROR", 0, acc,  rora, 2 },
/* 0x6B */ {  NULL, 0, NULL, NULL, 0 },
/* 0x6C */ { "JMP", 0, ind,  jmp, 5 },
/* 0x6D */ { "ADC", 0, abo,  adc, 4 },
/* 0x6E */ { "ROR", 0, abo,  ror, 6 },
/* 0x6F */ { "RRA", 1, abo,  rra, 6 },
/* 0x70 */ { "BVS", 0, rel,  bvs, 2 },
/* 0x71 */ { "ADC", 0, iiy,  adc, 5 },
/* 0x72 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x73 */ { "RRA", 1, iiy,  rra, 8 },
/* 0x74 */ { "NOP", 1, zpx,  nop, 4 },
/* 0x75 */ { "ADC", 0, zpx,  adc, 4 },
/* 0x76 */ { "ROR", 0, zpx,  ror, 6 },
/* 0x77 */ { "RRA", 1, zpx,  rra, 6 },
/* 0x78 */ { "SEI", 0, imp,  sei, 2 },
/* 0x79 */ { "ADC", 0, aby,  adc, 4 },
/* 0x7A */ { "NOP", 1, imp,  nop, 2 },
/* 0x7B */ { "RRA", 1, aby,  rra, 7 },
/* 0x7C */ { "NOP", 1, abx,  nop, 4 },
/* 0x7D */ { "ADC", 0, abx,  adc, 4 },
/* 0x7E */ { "ROR", 0, abx,  ror, 7 },
/* 0x7F */ { "RRA", 1, abx,  rra, 7 },
/* 0x80 */ { "NOP", 1, imm,  nop, 2 },
/* 0x81 */ { "STA", 0, iix,  sta, 6 },
/* 0x82 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x83 */ { "SAX", 1, iix,  sax, 6 },
/* 0x84 */ { "STY", 0, zpa,  sty, 3 },
/* 0x85 */ { "STA", 0, zpa,  sta, 3 },
/* 0x86 */ { "STX", 0, zpa,  stx, 3 },
/* 0x87 */ { "SAX", 1, zpa,  sax, 3 },
/* 0x88 */ { "DEY", 0, imp,  dey, 2 },
/* 0x89 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x8A */ { "TXA", 0, imp,  txa, 2 },
/* 0x8B */ {  NULL, 0, NULL, NULL, 0 },
/* 0x8C */ { "STY", 0, abo,  sty, 4 },
/* 0x8D */ { "STA", 0, abo,  sta, 4 },
/* 0x8E */ { "STX", 0, abo,  stx, 4 },
/* 0x8F */ { "SAX", 1, abo,  sax, 4 },
/* 0x90 */ { "BCC", 0, rel,  bcc, 2 },
/* 0x91 */ { "STA", 0, iiy,  sta, 6 },
/* 0x92 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x93 */ {  NULL, 0, NULL, NULL, 0 },
/* 0x94 */ { "STY", 0, zpx,  sty, 4 },
/* 0x95 */ { "STA", 0, zpx,  sta, 4 },
/* 0x96 */ { "STX", 0, zpy,  stx, 4 },
/* 0x97 */ { "SAX", 1, zpy,  sax, 4 },
/* 0x98 */ { "TYA", 0, imp,  tya, 2 },
/* 0x99 */ { "STA", 0, aby,  sta, 5 },
/* 0x9A */ { "TXS", 0, imp,  txs, 2 },
/* 0x9B */ {  NULL, 0, NULL, NULL, 0 },
/* 0x9C */ {  NULL, 0, NULL, NULL, 0 },
/* 0x9D */ { "STA", 0, abx,  sta, 5 },
/* 0x9E */ {  NULL, 0, NULL, NULL, 0 },
/* 0x9F */ {  NULL, 0, NULL, NULL, 0 },
/* 0xA0 */ { "LDY", 0, imm,  ldy, 2 },
/* 0xA1 */ { "LDA", 0, iix,  lda, 6 },
/* 0xA2 */ { "LDX", 0, imm,  ldx, 2 },
/* 0xA3 */ { "LAX", 1, iix,  lax, 6 },
/* 0xA4 */ { "LDY", 0, zpa,  ldy, 3 },
/* 0xA5 */ { "LDA", 0, zpa,  lda, 3 },
/* 0xA6 */ { "LDX", 0, zpa,  ldx, 3 },
/* 0xA7 */ { "LAX", 1, zpa,  lax, 3 },
/* 0xA8 */ { "TAY", 0, imp,  tay, 2 },
/* 0xA9 */ { "LDA", 0, imm,  lda, 2 },
/* 0xAA */ { "TAX", 0, imp,  tax, 2 },
/* 0xAB */ {  NULL, 0, NULL, NULL, 0 },
/* 0xAC */ { "LDY", 0, abo,  ldy, 4 },
/* 0xAD */ { "LDA", 0, abo,  lda, 4 },
/* 0xAE */ { "LDX", 0, abo,  ldx, 4 },
/* 0xAF */ { "LAX", 1, abo,  lax, 4 },
/* 0xB0 */ { "BCS", 0, rel,  bcs, 2 },
/* 0xB1 */ { "LDA", 0, iiy,  lda, 5 },
/* 0xB2 */ {  NULL, 0, NULL, NULL, 0 },
/* 0xB3 */ { "LAX", 1, iiy,  lax, 5 },
/* 0xB4 */ { "LDY", 0, zpx,  ldy, 4 },
/* 0xB5 */ { "LDA", 0, zpx,  lda, 4 },
/* 0xB6 */ { "LDX", 0, zpy,  ldx, 4 },
/* 0xB7 */ { "LAX", 1, zpy,  lax, 4 },
/* 0xB8 */ { "CLV", 0, imp,  clv, 2 },
/* 0xB9 */ { "LDA", 0, aby,  lda, 4 },
/* 0xBA */ { "TSX", 0, imp,  tsx, 2 },
/* 0xBB */ {  NULL, 0, NULL, NULL, 0 },
/* 0xBC */ { "LDY", 0, abx,  ldy, 4 },
/* 0xBD */ { "LDA", 0, abx,  lda, 4 },
/* 0xBE */ { "LDX", 0, aby,  ldx, 4 },
/* 0xBF */ { "LAX", 1, aby,  lax, 4 },
/* 0xC0 */ { "CPY", 0, imm,  cpy, 2 },
/* 0xC1 */ { "CMP", 0, iix,  cmp, 6 },
/* 0xC2 */ {  NULL, 0, NULL, NULL, 0 },
/* 0xC3 */ { "DCP", 1, iix,  dcp, 8 },
/* 0xC4 */ { "CPY", 0, zpa,  cpy, 3 },
/* 0xC5 */ { "CMP", 0, zpa,  cmp, 3 },
/* 0xC6 */ { "DEC", 0, zpa,  dec, 5 },
/* 0xC7 */ { "DCP", 1, zpa,  dcp, 5 },
/* 0xC8 */ { "INY", 0, imp,  iny, 2 },
/* 0xC9 */ { "CMP", 0, imm,  cmp, 2 },
/* 0xCA */ { "DEX", 0, imp,  dex, 2 },
/* 0xCB */ {  NULL, 0, NULL, NULL, 0 },
/* 0xCC */ { "CPY", 0, abo,  cpy, 4 },
/* 0xCD */ { "CMP", 0, abo,  cmp, 4 },
/* 0xCE */ { "DEC", 0, abo,  dec, 6 },
/* 0xCF */ { "DCP", 1, abo,  dcp, 6 },
/* 0xD0 */ { "BNE", 0, rel,  bne, 2 },
/* 0xD1 */ { "CMP", 0, iiy,  cmp, 5 },
/* 0xD2 */ {  NULL, 0, NULL, NULL, 0 },
/* 0xD3 */ { "DCP", 1, iiy,  dcp, 8 },
/* 0xD4 */ { "NOP", 1, zpx,  nop, 4 },
/* 0xD5 */ { "CMP", 0, zpx,  cmp, 4 },
/* 0xD6 */ { "DEC", 0, zpx,  dec, 6 },
/* 0xD7 */ { "DCP", 1, zpx,  dcp, 6 },
/* 0xD8 */ { "CLD", 0, imp,  cld, 2 },
/* 0xD9 */ { "CMP", 0, aby,  cmp, 4 },
/* 0xDA */ { "NOP", 1, imp,  nop, 2 },
/* 0xDB */ { "DCP", 1, aby,  dcp, 7 },
/* 0xDC */ { "NOP", 1, abx,  nop, 4 },
/* 0xDD */ { "CMP", 0, abx,  cmp, 4 },
/* 0xDE */ { "DEC", 0, abx,  dec, 7 },
/* 0xDF */ { "DCP", 1, abx,  dcp, 7 },
/* 0xE0 */ { "CPX", 0, imm,  cpx, 2 },
/* 0xE1 */ { "SBC", 0, iix,  sbc, 6 },
/* 0xE2 */ {  NULL, 0, NULL, NULL, 0 },
/* 0xE3 */ { "ISB", 1, iix,  isb, 8 },
/* 0xE4 */ { "CPX", 0, zpa,  cpx, 3 },
/* 0xE5 */ { "SBC", 0, zpa,  sbc, 3 },
/* 0xE6 */ { "INC", 0, zpa,  inc, 5 },
/* 0xE7 */ { "ISB", 1, zpa,  isb, 5 },
/* 0xE8 */ { "INX", 0, imp,  inx, 2 },
/* 0xE9 */ { "SBC", 0, imm,  sbc, 2 },
/* 0xEA */ { "NOP", 0, imp,  nop, 2 },
/* 0xEB */ { "SBC", 1, imm,  sbc, 2 },
/* 0xEC */ { "CPX", 0, abo,  cpx, 4 },
/* 0xED */ { "SBC", 0, abo,  sbc, 4 },
/* 0xEE */ { "INC", 0, abo,  inc, 6 },
/* 0xEF */ { "ISB", 1, abo,  isb, 6 },
/* 0xF0 */ { "BEQ", 0, rel,  beq, 2 },
/* 0xF1 */ { "SBC", 0, iiy,  sbc, 5 },
/* 0xF2 */ {  NULL, 0, NULL, NULL, 0 },
/* 0xF3 */ { "ISB", 1, iiy,  isb, 8 },
/* 0xF4 */ { "NOP", 1, zpx,  nop, 4 },
/* 0xF5 */ { "SBC", 0, zpx,  sbc, 4 },
/* 0xF6 */ { "INC", 0, zpx,  inc, 6 },
/* 0xF7 */ { "ISB", 1, zpx,  isb, 6 },
/* 0xF8 */ { "SED", 0, imp,  sed, 2 },
/* 0xF9 */ { "SBC", 0, aby,  sbc, 4 },
/* 0xFA */ { "NOP", 1, imp,  nop, 2 },
/* 0xFB */ { "ISB", 1, aby,  isb, 7 },
/* 0xFC */ { "NOP", 1, abx,  nop, 4 },
/* 0xFD */ { "SBC", 0, abx,  sbc, 4 },
/* 0xFE */ { "INC", 0, abx,  inc, 7 },
/* 0xFF */ { "ISB", 1, abx,  isb, 7 }
};