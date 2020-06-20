#include <stddef.h>
#include "event/clear_oam.h"
#include "event/clear_vertical_blank.h"
#include "event/evaluate_sprite.h"
#include "event/increment_vram_x.h"
#include "event/increment_vram_y.h"
#include "event/load_palette_id.h"
#include "event/load_shifters.h"
#include "event/load_sprite.h"
#include "event/load_tile_high.h"
#include "event/load_tile_id.h"
#include "event/load_tile_low.h"
#include "event/load_vram_x.h"
#include "event/load_vram_y.h"
#include "event/render_pixel.h"
#include "event/set_vertical_blank.h"
#include "event/update_sprite_shifters.h"
#include "event/update_tile_shifters.h"
#include "event.h"

#define ID NULL
#define LT &load_tile_id
#define LP &load_palette_id
#define LH &load_tile_high
#define LL &load_tile_low
#define LS &load_shifters
#define BS &update_tile_shifters
#define LX &load_vram_x
#define LY &load_vram_y
#define IX &increment_vram_x
#define IY &increment_vram_y
#define RP &render_pixel
#define CV &clear_vertical_blank
#define SV &set_vertical_blank
#define CO &clear_oam
#define FS &update_sprite_shifters
#define ES &evaluate_sprite
#define SS &load_sprite

#define visible_scanline {\
/* 000 */ { ID                },\
/* 001 */ { RP,LS,LT,BS,FS,CO },\
/* 002 */ { RP,BS,FS          },\
/* 003 */ { RP,LP,BS,FS       },\
/* 004 */ { RP,BS,FS          },\
/* 005 */ { RP,LL,BS,FS       },\
/* 006 */ { RP,BS,FS          },\
/* 007 */ { RP,LH,BS,FS       },\
/* 008 */ { RP,IX,BS,FS       },\
/* 009 */ { RP,LS,LT,BS,FS    },\
/* 010 */ { RP,BS,FS          },\
/* 011 */ { RP,LP,BS,FS       },\
/* 012 */ { RP,BS,FS          },\
/* 013 */ { RP,LL,BS,FS       },\
/* 014 */ { RP,BS,FS          },\
/* 015 */ { RP,LH,BS,FS       },\
/* 016 */ { RP,IX,BS,FS       },\
/* 017 */ { RP,LS,LT,BS,FS    },\
/* 018 */ { RP,BS,FS          },\
/* 019 */ { RP,LP,BS,FS       },\
/* 020 */ { RP,BS,FS          },\
/* 021 */ { RP,LL,BS,FS       },\
/* 022 */ { RP,BS,FS          },\
/* 023 */ { RP,LH,BS,FS       },\
/* 024 */ { RP,IX,BS,FS       },\
/* 025 */ { RP,LS,LT,BS,FS    },\
/* 026 */ { RP,BS,FS          },\
/* 027 */ { RP,LP,BS,FS       },\
/* 028 */ { RP,BS,FS          },\
/* 029 */ { RP,LL,BS,FS       },\
/* 030 */ { RP,BS,FS          },\
/* 031 */ { RP,LH,BS,FS       },\
/* 032 */ { RP,IX,BS,FS       },\
/* 033 */ { RP,LS,LT,BS,FS    },\
/* 034 */ { RP,BS,FS          },\
/* 035 */ { RP,LP,BS,FS       },\
/* 036 */ { RP,BS,FS          },\
/* 037 */ { RP,LL,BS,FS       },\
/* 038 */ { RP,BS,FS          },\
/* 039 */ { RP,LH,BS,FS       },\
/* 040 */ { RP,IX,BS,FS       },\
/* 041 */ { RP,LS,LT,BS,FS    },\
/* 042 */ { RP,BS,FS          },\
/* 043 */ { RP,LP,BS,FS       },\
/* 044 */ { RP,BS,FS          },\
/* 045 */ { RP,LL,BS,FS       },\
/* 046 */ { RP,BS,FS          },\
/* 047 */ { RP,LH,BS,FS       },\
/* 048 */ { RP,IX,BS,FS       },\
/* 049 */ { RP,LS,LT,BS,FS    },\
/* 050 */ { RP,BS,FS          },\
/* 051 */ { RP,LP,BS,FS       },\
/* 052 */ { RP,BS,FS          },\
/* 053 */ { RP,LL,BS,FS       },\
/* 054 */ { RP,BS,FS          },\
/* 055 */ { RP,LH,BS,FS       },\
/* 056 */ { RP,IX,BS,FS       },\
/* 057 */ { RP,LS,LT,BS,FS    },\
/* 058 */ { RP,BS,FS          },\
/* 059 */ { RP,LP,BS,FS       },\
/* 060 */ { RP,BS,FS          },\
/* 061 */ { RP,LL,BS,FS       },\
/* 062 */ { RP,BS,FS          },\
/* 063 */ { RP,LH,BS,FS       },\
/* 064 */ { RP,IX,BS,FS       },\
/* 065 */ { RP,LS,LT,BS,FS,ES },\
/* 066 */ { RP,BS,FS,ES       },\
/* 067 */ { RP,LP,BS,FS,ES    },\
/* 068 */ { RP,BS,FS,ES       },\
/* 069 */ { RP,LL,BS,FS,ES    },\
/* 070 */ { RP,BS,FS,ES       },\
/* 071 */ { RP,LH,BS,FS,ES    },\
/* 072 */ { RP,IX,BS,FS,ES    },\
/* 073 */ { RP,LS,LT,BS,FS,ES },\
/* 074 */ { RP,BS,FS,ES       },\
/* 075 */ { RP,LP,BS,FS,ES    },\
/* 076 */ { RP,BS,FS,ES       },\
/* 077 */ { RP,LL,BS,FS,ES    },\
/* 078 */ { RP,BS,FS,ES       },\
/* 079 */ { RP,LH,BS,FS,ES    },\
/* 080 */ { RP,IX,BS,FS,ES    },\
/* 081 */ { RP,LS,LT,BS,FS,ES },\
/* 082 */ { RP,BS,FS,ES       },\
/* 083 */ { RP,LP,BS,FS,ES    },\
/* 084 */ { RP,BS,FS,ES       },\
/* 085 */ { RP,LL,BS,FS,ES    },\
/* 086 */ { RP,BS,FS,ES       },\
/* 087 */ { RP,LH,BS,FS,ES    },\
/* 088 */ { RP,IX,BS,FS,ES    },\
/* 089 */ { RP,LS,LT,BS,FS,ES },\
/* 090 */ { RP,BS,FS,ES       },\
/* 091 */ { RP,LP,BS,FS,ES    },\
/* 092 */ { RP,BS,FS,ES       },\
/* 093 */ { RP,LL,BS,FS,ES    },\
/* 094 */ { RP,BS,FS,ES       },\
/* 095 */ { RP,LH,BS,FS,ES    },\
/* 096 */ { RP,IX,BS,FS,ES    },\
/* 097 */ { RP,LS,LT,BS,FS,ES },\
/* 098 */ { RP,BS,FS,ES       },\
/* 099 */ { RP,LP,BS,FS,ES    },\
/* 100 */ { RP,BS,FS,ES       },\
/* 101 */ { RP,LL,BS,FS,ES    },\
/* 102 */ { RP,BS,FS,ES       },\
/* 103 */ { RP,LH,BS,FS,ES    },\
/* 104 */ { RP,IX,BS,FS,ES    },\
/* 105 */ { RP,LS,LT,BS,FS,ES },\
/* 106 */ { RP,BS,FS,ES       },\
/* 107 */ { RP,LP,BS,FS,ES    },\
/* 108 */ { RP,BS,FS,ES       },\
/* 109 */ { RP,LL,BS,FS,ES    },\
/* 110 */ { RP,BS,FS,ES       },\
/* 111 */ { RP,LH,BS,FS,ES    },\
/* 112 */ { RP,IX,BS,FS,ES    },\
/* 113 */ { RP,LS,LT,BS,FS,ES },\
/* 114 */ { RP,BS,FS,ES       },\
/* 115 */ { RP,LP,BS,FS,ES    },\
/* 116 */ { RP,BS,FS,ES       },\
/* 117 */ { RP,LL,BS,FS,ES    },\
/* 118 */ { RP,BS,FS,ES       },\
/* 119 */ { RP,LH,BS,FS,ES    },\
/* 120 */ { RP,IX,BS,FS,ES    },\
/* 121 */ { RP,LS,LT,BS,FS,ES },\
/* 122 */ { RP,BS,FS,ES       },\
/* 123 */ { RP,LP,BS,FS,ES    },\
/* 124 */ { RP,BS,FS,ES       },\
/* 125 */ { RP,LL,BS,FS,ES    },\
/* 126 */ { RP,BS,FS,ES       },\
/* 127 */ { RP,LH,BS,FS,ES    },\
/* 128 */ { RP,IX,BS,FS,ES    },\
/* 129 */ { RP,LS,LT,BS,FS    },\
/* 130 */ { RP,BS,FS          },\
/* 131 */ { RP,LP,BS,FS       },\
/* 132 */ { RP,BS,FS          },\
/* 133 */ { RP,LL,BS,FS       },\
/* 134 */ { RP,BS,FS          },\
/* 135 */ { RP,LH,BS,FS       },\
/* 136 */ { RP,IX,BS,FS       },\
/* 137 */ { RP,LS,LT,BS,FS    },\
/* 138 */ { RP,BS,FS          },\
/* 139 */ { RP,LP,BS,FS       },\
/* 140 */ { RP,BS,FS          },\
/* 141 */ { RP,LL,BS,FS       },\
/* 142 */ { RP,BS,FS          },\
/* 143 */ { RP,LH,BS,FS       },\
/* 144 */ { RP,IX,BS,FS       },\
/* 145 */ { RP,LS,LT,BS,FS    },\
/* 146 */ { RP,BS,FS          },\
/* 147 */ { RP,LP,BS,FS       },\
/* 148 */ { RP,BS,FS          },\
/* 149 */ { RP,LL,BS,FS       },\
/* 150 */ { RP,BS,FS          },\
/* 151 */ { RP,LH,BS,FS       },\
/* 152 */ { RP,IX,BS,FS       },\
/* 153 */ { RP,LS,LT,BS,FS    },\
/* 154 */ { RP,BS,FS          },\
/* 155 */ { RP,LP,BS,FS       },\
/* 156 */ { RP,BS,FS          },\
/* 157 */ { RP,LL,BS,FS       },\
/* 158 */ { RP,BS,FS          },\
/* 159 */ { RP,LH,BS,FS       },\
/* 160 */ { RP,IX,BS,FS       },\
/* 161 */ { RP,LS,LT,BS,FS    },\
/* 162 */ { RP,BS,FS          },\
/* 163 */ { RP,LP,BS,FS       },\
/* 164 */ { RP,BS,FS          },\
/* 165 */ { RP,LL,BS,FS       },\
/* 166 */ { RP,BS,FS          },\
/* 167 */ { RP,LH,BS,FS       },\
/* 168 */ { RP,IX,BS,FS       },\
/* 169 */ { RP,LS,LT,BS,FS    },\
/* 170 */ { RP,BS,FS          },\
/* 171 */ { RP,LP,BS,FS       },\
/* 172 */ { RP,BS,FS          },\
/* 173 */ { RP,LL,BS,FS       },\
/* 174 */ { RP,BS,FS          },\
/* 175 */ { RP,LH,BS,FS       },\
/* 176 */ { RP,IX,BS,FS       },\
/* 177 */ { RP,LS,LT,BS,FS    },\
/* 178 */ { RP,BS,FS          },\
/* 179 */ { RP,LP,BS,FS       },\
/* 180 */ { RP,BS,FS          },\
/* 181 */ { RP,LL,BS,FS       },\
/* 182 */ { RP,BS,FS          },\
/* 183 */ { RP,LH,BS,FS       },\
/* 184 */ { RP,IX,BS,FS       },\
/* 185 */ { RP,LS,LT,BS,FS    },\
/* 186 */ { RP,BS,FS          },\
/* 187 */ { RP,LP,BS,FS       },\
/* 188 */ { RP,BS,FS          },\
/* 189 */ { RP,LL,BS,FS       },\
/* 190 */ { RP,BS,FS          },\
/* 191 */ { RP,LH,BS,FS       },\
/* 192 */ { RP,IX,BS,FS       },\
/* 193 */ { RP,LS,LT,BS,FS    },\
/* 194 */ { RP,BS,FS          },\
/* 195 */ { RP,LP,BS,FS       },\
/* 196 */ { RP,BS,FS          },\
/* 197 */ { RP,LL,BS,FS       },\
/* 198 */ { RP,BS,FS          },\
/* 199 */ { RP,LH,BS,FS       },\
/* 200 */ { RP,IX,BS,FS       },\
/* 201 */ { RP,LS,LT,BS,FS    },\
/* 202 */ { RP,BS,FS          },\
/* 203 */ { RP,LP,BS,FS       },\
/* 204 */ { RP,BS,FS          },\
/* 205 */ { RP,LL,BS,FS       },\
/* 206 */ { RP,BS,FS          },\
/* 207 */ { RP,LH,BS,FS       },\
/* 208 */ { RP,IX,BS,FS       },\
/* 209 */ { RP,LS,LT,BS,FS    },\
/* 210 */ { RP,BS,FS          },\
/* 211 */ { RP,LP,BS,FS       },\
/* 212 */ { RP,BS,FS          },\
/* 213 */ { RP,LL,BS,FS       },\
/* 214 */ { RP,BS,FS          },\
/* 215 */ { RP,LH,BS,FS       },\
/* 216 */ { RP,IX,BS,FS       },\
/* 217 */ { RP,LS,LT,BS,FS    },\
/* 218 */ { RP,BS,FS          },\
/* 219 */ { RP,LP,BS,FS       },\
/* 220 */ { RP,BS,FS          },\
/* 221 */ { RP,LL,BS,FS       },\
/* 222 */ { RP,BS,FS          },\
/* 223 */ { RP,LH,BS,FS       },\
/* 224 */ { RP,IX,BS,FS       },\
/* 225 */ { RP,LS,LT,BS,FS    },\
/* 226 */ { RP,BS,FS          },\
/* 227 */ { RP,LP,BS,FS       },\
/* 228 */ { RP,BS,FS          },\
/* 229 */ { RP,LL,BS,FS       },\
/* 230 */ { RP,BS,FS          },\
/* 231 */ { RP,LH,BS,FS       },\
/* 232 */ { RP,IX,BS,FS       },\
/* 233 */ { RP,LS,LT,BS,FS    },\
/* 234 */ { RP,BS,FS          },\
/* 235 */ { RP,LP,BS,FS       },\
/* 236 */ { RP,BS,FS          },\
/* 237 */ { RP,LL,BS,FS       },\
/* 238 */ { RP,BS,FS          },\
/* 239 */ { RP,LH,BS,FS       },\
/* 240 */ { RP,IX,BS,FS       },\
/* 241 */ { RP,LS,LT,BS,FS    },\
/* 242 */ { RP,BS,FS          },\
/* 243 */ { RP,LP,BS,FS       },\
/* 244 */ { RP,BS,FS          },\
/* 245 */ { RP,LL,BS,FS       },\
/* 246 */ { RP,BS,FS          },\
/* 247 */ { RP,LH,BS,FS       },\
/* 248 */ { RP,IX,BS,FS       },\
/* 249 */ { RP,LS,LT,BS,FS    },\
/* 250 */ { RP,BS,FS          },\
/* 251 */ { RP,LP,BS,FS       },\
/* 252 */ { RP,BS,FS          },\
/* 253 */ { RP,LL,BS,FS       },\
/* 254 */ { RP,BS,FS          },\
/* 255 */ { RP,LH,BS,FS       },\
/* 256 */ { RP,IY,BS,FS       },\
/* 257 */ { LX,SS             },\
/* 258 */ { ID                },\
/* 259 */ { ID                },\
/* 260 */ { ID                },\
/* 261 */ { ID                },\
/* 262 */ { ID                },\
/* 263 */ { ID                },\
/* 264 */ { ID                },\
/* 265 */ { SS                },\
/* 266 */ { ID                },\
/* 267 */ { ID                },\
/* 268 */ { ID                },\
/* 269 */ { ID                },\
/* 270 */ { ID                },\
/* 271 */ { ID                },\
/* 272 */ { ID                },\
/* 273 */ { SS                },\
/* 274 */ { ID                },\
/* 275 */ { ID                },\
/* 276 */ { ID                },\
/* 277 */ { ID                },\
/* 278 */ { ID                },\
/* 279 */ { ID                },\
/* 280 */ { ID                },\
/* 281 */ { SS                },\
/* 282 */ { ID                },\
/* 283 */ { ID                },\
/* 284 */ { ID                },\
/* 285 */ { ID                },\
/* 286 */ { ID                },\
/* 287 */ { ID                },\
/* 288 */ { ID                },\
/* 289 */ { SS                },\
/* 290 */ { ID                },\
/* 291 */ { ID                },\
/* 292 */ { ID                },\
/* 293 */ { ID                },\
/* 294 */ { ID                },\
/* 295 */ { ID                },\
/* 296 */ { ID                },\
/* 297 */ { SS                },\
/* 298 */ { ID                },\
/* 299 */ { ID                },\
/* 300 */ { ID                },\
/* 301 */ { ID                },\
/* 302 */ { ID                },\
/* 303 */ { ID                },\
/* 304 */ { ID                },\
/* 305 */ { SS                },\
/* 306 */ { ID                },\
/* 307 */ { ID                },\
/* 308 */ { ID                },\
/* 309 */ { ID                },\
/* 310 */ { ID                },\
/* 311 */ { ID                },\
/* 312 */ { ID                },\
/* 313 */ { SS                },\
/* 314 */ { ID                },\
/* 315 */ { ID                },\
/* 316 */ { ID                },\
/* 317 */ { ID                },\
/* 318 */ { ID                },\
/* 319 */ { ID                },\
/* 320 */ { ID                },\
/* 321 */ { LS,LT,BS          },\
/* 322 */ { BS                },\
/* 323 */ { LP,BS             },\
/* 324 */ { BS                },\
/* 325 */ { LL,BS             },\
/* 326 */ { BS                },\
/* 327 */ { LH,BS             },\
/* 328 */ { IX,BS             },\
/* 329 */ { LS,LT,BS          },\
/* 330 */ { BS                },\
/* 331 */ { LP,BS             },\
/* 332 */ { BS                },\
/* 333 */ { LL,BS             },\
/* 334 */ { BS                },\
/* 335 */ { LH,BS             },\
/* 336 */ { IX,BS             },\
/* 337 */ { LS,LT             },\
/* 338 */ { ID                },\
/* 339 */ { LS,LT             },\
/* 340 */ { ID                } \
}

#define pre_render_scanline {\
/* 000 */ { ID                },\
/* 001 */ { CV,LS,LT,BS,FS    },\
/* 002 */ { BS,FS             },\
/* 003 */ { LP,BS,FS          },\
/* 004 */ { BS,FS             },\
/* 005 */ { LL,BS,FS          },\
/* 006 */ { BS,FS             },\
/* 007 */ { LH,BS,FS          },\
/* 008 */ { IX,BS,FS          },\
/* 009 */ { LS,LT,BS,FS       },\
/* 010 */ { BS,FS             },\
/* 011 */ { LP,BS,FS          },\
/* 012 */ { BS,FS             },\
/* 013 */ { LL,BS,FS          },\
/* 014 */ { BS,FS             },\
/* 015 */ { LH,BS,FS          },\
/* 016 */ { IX,BS,FS          },\
/* 017 */ { LS,LT,BS,FS       },\
/* 018 */ { BS,FS             },\
/* 019 */ { LP,BS,FS          },\
/* 020 */ { BS,FS             },\
/* 021 */ { LL,BS,FS          },\
/* 022 */ { BS,FS             },\
/* 023 */ { LH,BS,FS          },\
/* 024 */ { IX,BS,FS          },\
/* 025 */ { LS,LT,BS,FS       },\
/* 026 */ { BS,FS             },\
/* 027 */ { LP,BS,FS          },\
/* 028 */ { BS,FS             },\
/* 029 */ { LL,BS,FS          },\
/* 030 */ { BS,FS             },\
/* 031 */ { LH,BS,FS          },\
/* 032 */ { IX,BS,FS          },\
/* 033 */ { LS,LT,BS,FS       },\
/* 034 */ { BS,FS             },\
/* 035 */ { LP,BS,FS          },\
/* 036 */ { BS,FS             },\
/* 037 */ { LL,BS,FS          },\
/* 038 */ { BS,FS             },\
/* 039 */ { LH,BS,FS          },\
/* 040 */ { IX,BS,FS          },\
/* 041 */ { LS,LT,BS,FS       },\
/* 042 */ { BS,FS             },\
/* 043 */ { LP,BS,FS          },\
/* 044 */ { BS,FS             },\
/* 045 */ { LL,BS,FS          },\
/* 046 */ { BS,FS             },\
/* 047 */ { LH,BS,FS          },\
/* 048 */ { IX,BS,FS          },\
/* 049 */ { LS,LT,BS,FS       },\
/* 050 */ { BS,FS             },\
/* 051 */ { LP,BS,FS          },\
/* 052 */ { BS,FS             },\
/* 053 */ { LL,BS,FS          },\
/* 054 */ { BS,FS             },\
/* 055 */ { LH,BS,FS          },\
/* 056 */ { IX,BS,FS          },\
/* 057 */ { LS,LT,BS,FS       },\
/* 058 */ { BS,FS             },\
/* 059 */ { LP,BS,FS          },\
/* 060 */ { BS,FS             },\
/* 061 */ { LL,BS,FS          },\
/* 062 */ { BS,FS             },\
/* 063 */ { LH,BS,FS          },\
/* 064 */ { IX,BS,FS          },\
/* 065 */ { LS,LT,BS,FS       },\
/* 066 */ { BS,FS             },\
/* 067 */ { LP,BS,FS          },\
/* 068 */ { BS,FS             },\
/* 069 */ { LL,BS,FS          },\
/* 070 */ { BS,FS             },\
/* 071 */ { LH,BS,FS          },\
/* 072 */ { IX,BS,FS          },\
/* 073 */ { LS,LT,BS,FS       },\
/* 074 */ { BS,FS             },\
/* 075 */ { LP,BS,FS          },\
/* 076 */ { BS,FS             },\
/* 077 */ { LL,BS,FS          },\
/* 078 */ { BS,FS             },\
/* 079 */ { LH,BS,FS          },\
/* 080 */ { IX,BS,FS          },\
/* 081 */ { LS,LT,BS,FS       },\
/* 082 */ { BS,FS             },\
/* 083 */ { LP,BS,FS          },\
/* 084 */ { BS,FS             },\
/* 085 */ { LL,BS,FS          },\
/* 086 */ { BS,FS             },\
/* 087 */ { LH,BS,FS          },\
/* 088 */ { IX,BS,FS          },\
/* 089 */ { LS,LT,BS,FS       },\
/* 090 */ { BS,FS             },\
/* 091 */ { LP,BS,FS          },\
/* 092 */ { BS,FS             },\
/* 093 */ { LL,BS,FS          },\
/* 094 */ { BS,FS             },\
/* 095 */ { LH,BS,FS          },\
/* 096 */ { IX,BS,FS          },\
/* 097 */ { LS,LT,BS,FS       },\
/* 098 */ { BS,FS             },\
/* 099 */ { LP,BS,FS          },\
/* 100 */ { BS,FS             },\
/* 101 */ { LL,BS,FS          },\
/* 102 */ { BS,FS             },\
/* 103 */ { LH,BS,FS          },\
/* 104 */ { IX,BS,FS          },\
/* 105 */ { LS,LT,BS,FS       },\
/* 106 */ { BS,FS             },\
/* 107 */ { LP,BS,FS          },\
/* 108 */ { BS,FS             },\
/* 109 */ { LL,BS,FS          },\
/* 110 */ { BS,FS             },\
/* 111 */ { LH,BS,FS          },\
/* 112 */ { IX,BS,FS          },\
/* 113 */ { LS,LT,BS,FS       },\
/* 114 */ { BS,FS             },\
/* 115 */ { LP,BS,FS          },\
/* 116 */ { BS,FS             },\
/* 117 */ { LL,BS,FS          },\
/* 118 */ { BS,FS             },\
/* 119 */ { LH,BS,FS          },\
/* 120 */ { IX,BS,FS          },\
/* 121 */ { LS,LT,BS,FS       },\
/* 122 */ { BS,FS             },\
/* 123 */ { LP,BS,FS          },\
/* 124 */ { BS,FS             },\
/* 125 */ { LL,BS,FS          },\
/* 126 */ { BS,FS             },\
/* 127 */ { LH,BS,FS          },\
/* 128 */ { IX,BS,FS          },\
/* 129 */ { LS,LT,BS,FS       },\
/* 130 */ { BS,FS             },\
/* 131 */ { LP,BS,FS          },\
/* 132 */ { BS,FS             },\
/* 133 */ { LL,BS,FS          },\
/* 134 */ { BS,FS             },\
/* 135 */ { LH,BS,FS          },\
/* 136 */ { IX,BS,FS          },\
/* 137 */ { LS,LT,BS,FS       },\
/* 138 */ { BS,FS             },\
/* 139 */ { LP,BS,FS          },\
/* 140 */ { BS,FS             },\
/* 141 */ { LL,BS,FS          },\
/* 142 */ { BS,FS             },\
/* 143 */ { LH,BS,FS          },\
/* 144 */ { IX,BS,FS          },\
/* 145 */ { LS,LT,BS,FS       },\
/* 146 */ { BS,FS             },\
/* 147 */ { LP,BS,FS          },\
/* 148 */ { BS,FS             },\
/* 149 */ { LL,BS,FS          },\
/* 150 */ { BS,FS             },\
/* 151 */ { LH,BS,FS          },\
/* 152 */ { IX,BS,FS          },\
/* 153 */ { LS,LT,BS,FS       },\
/* 154 */ { BS,FS             },\
/* 155 */ { LP,BS,FS          },\
/* 156 */ { BS,FS             },\
/* 157 */ { LL,BS,FS          },\
/* 158 */ { BS,FS             },\
/* 159 */ { LH,BS,FS          },\
/* 160 */ { IX,BS,FS          },\
/* 161 */ { LS,LT,BS,FS       },\
/* 162 */ { BS,FS             },\
/* 163 */ { LP,BS,FS          },\
/* 164 */ { BS,FS             },\
/* 165 */ { LL,BS,FS          },\
/* 166 */ { BS,FS             },\
/* 167 */ { LH,BS,FS          },\
/* 168 */ { IX,BS,FS          },\
/* 169 */ { LS,LT,BS,FS       },\
/* 170 */ { BS,FS             },\
/* 171 */ { LP,BS,FS          },\
/* 172 */ { BS,FS             },\
/* 173 */ { LL,BS,FS          },\
/* 174 */ { BS,FS             },\
/* 175 */ { LH,BS,FS          },\
/* 176 */ { IX,BS,FS          },\
/* 177 */ { LS,LT,BS,FS       },\
/* 178 */ { BS,FS             },\
/* 179 */ { LP,BS,FS          },\
/* 180 */ { BS,FS             },\
/* 181 */ { LL,BS,FS          },\
/* 182 */ { BS,FS             },\
/* 183 */ { LH,BS,FS          },\
/* 184 */ { IX,BS,FS          },\
/* 185 */ { LS,LT,BS,FS       },\
/* 186 */ { BS,FS             },\
/* 187 */ { LP,BS,FS          },\
/* 188 */ { BS,FS             },\
/* 189 */ { LL,BS,FS          },\
/* 190 */ { BS,FS             },\
/* 191 */ { LH,BS,FS          },\
/* 192 */ { IX,BS,FS          },\
/* 193 */ { LS,LT,BS,FS       },\
/* 194 */ { BS,FS             },\
/* 195 */ { LP,BS,FS          },\
/* 196 */ { BS,FS             },\
/* 197 */ { LL,BS,FS          },\
/* 198 */ { BS,FS             },\
/* 199 */ { LH,BS,FS          },\
/* 200 */ { IX,BS,FS          },\
/* 201 */ { LS,LT,BS,FS       },\
/* 202 */ { BS,FS             },\
/* 203 */ { LP,BS,FS          },\
/* 204 */ { BS,FS             },\
/* 205 */ { LL,BS,FS          },\
/* 206 */ { BS,FS             },\
/* 207 */ { LH,BS,FS          },\
/* 208 */ { IX,BS,FS          },\
/* 209 */ { LS,LT,BS,FS       },\
/* 210 */ { BS,FS             },\
/* 211 */ { LP,BS,FS          },\
/* 212 */ { BS,FS             },\
/* 213 */ { LL,BS,FS          },\
/* 214 */ { BS,FS             },\
/* 215 */ { LH,BS,FS          },\
/* 216 */ { IX,BS,FS          },\
/* 217 */ { LS,LT,BS,FS       },\
/* 218 */ { BS,FS             },\
/* 219 */ { LP,BS,FS          },\
/* 220 */ { BS,FS             },\
/* 221 */ { LL,BS,FS          },\
/* 222 */ { BS,FS             },\
/* 223 */ { LH,BS,FS          },\
/* 224 */ { IX,BS,FS          },\
/* 225 */ { LS,LT,BS,FS       },\
/* 226 */ { BS,FS             },\
/* 227 */ { LP,BS,FS          },\
/* 228 */ { BS,FS             },\
/* 229 */ { LL,BS,FS          },\
/* 230 */ { BS,FS             },\
/* 231 */ { LH,BS,FS          },\
/* 232 */ { IX,BS,FS          },\
/* 233 */ { LS,LT,BS,FS       },\
/* 234 */ { BS,FS             },\
/* 235 */ { LP,BS,FS          },\
/* 236 */ { BS,FS             },\
/* 237 */ { LL,BS,FS          },\
/* 238 */ { BS,FS             },\
/* 239 */ { LH,BS,FS          },\
/* 240 */ { IX,BS,FS          },\
/* 241 */ { LS,LT,BS,FS       },\
/* 242 */ { BS,FS             },\
/* 243 */ { LP,BS,FS          },\
/* 244 */ { BS,FS             },\
/* 245 */ { LL,BS,FS          },\
/* 246 */ { BS,FS             },\
/* 247 */ { LH,BS,FS          },\
/* 248 */ { IX,BS,FS          },\
/* 249 */ { LS,LT,BS,FS       },\
/* 250 */ { BS,FS             },\
/* 251 */ { LP,BS,FS          },\
/* 252 */ { BS,FS             },\
/* 253 */ { LL,BS,FS          },\
/* 254 */ { BS,FS             },\
/* 255 */ { LH,BS,FS          },\
/* 256 */ { IY,BS,FS          },\
/* 257 */ { LX,SS             },\
/* 258 */ { ID                },\
/* 259 */ { ID                },\
/* 260 */ { ID                },\
/* 261 */ { ID                },\
/* 262 */ { ID                },\
/* 263 */ { ID                },\
/* 264 */ { ID                },\
/* 265 */ { SS                },\
/* 266 */ { ID                },\
/* 267 */ { ID                },\
/* 268 */ { ID                },\
/* 269 */ { ID                },\
/* 270 */ { ID                },\
/* 271 */ { ID                },\
/* 272 */ { ID                },\
/* 273 */ { SS                },\
/* 274 */ { ID                },\
/* 275 */ { ID                },\
/* 276 */ { ID                },\
/* 277 */ { ID                },\
/* 278 */ { ID                },\
/* 279 */ { ID                },\
/* 280 */ { LY                },\
/* 281 */ { LY,SS             },\
/* 282 */ { LY                },\
/* 283 */ { LY                },\
/* 284 */ { LY                },\
/* 285 */ { LY                },\
/* 286 */ { LY                },\
/* 287 */ { LY                },\
/* 288 */ { LY                },\
/* 289 */ { LY,SS             },\
/* 290 */ { LY                },\
/* 291 */ { LY                },\
/* 292 */ { LY                },\
/* 293 */ { LY                },\
/* 294 */ { LY                },\
/* 295 */ { LY                },\
/* 296 */ { LY                },\
/* 297 */ { LY,SS             },\
/* 298 */ { LY                },\
/* 299 */ { LY                },\
/* 300 */ { LY                },\
/* 301 */ { LY                },\
/* 302 */ { LY                },\
/* 303 */ { LY                },\
/* 304 */ { LY                },\
/* 305 */ { SS                },\
/* 306 */ { ID                },\
/* 307 */ { ID                },\
/* 308 */ { ID                },\
/* 309 */ { ID                },\
/* 310 */ { ID                },\
/* 311 */ { ID                },\
/* 312 */ { ID                },\
/* 313 */ { SS                },\
/* 314 */ { ID                },\
/* 315 */ { ID                },\
/* 316 */ { ID                },\
/* 317 */ { ID                },\
/* 318 */ { ID                },\
/* 319 */ { ID                },\
/* 320 */ { ID                },\
/* 321 */ { LS,LT,BS          },\
/* 322 */ { BS                },\
/* 323 */ { LP,BS             },\
/* 324 */ { BS                },\
/* 325 */ { LL,BS             },\
/* 326 */ { BS                },\
/* 327 */ { LH,BS             },\
/* 328 */ { IX,BS             },\
/* 329 */ { LS,LT,BS          },\
/* 330 */ { BS                },\
/* 331 */ { LP,BS             },\
/* 332 */ { BS                },\
/* 333 */ { LL,BS             },\
/* 334 */ { BS                },\
/* 335 */ { LH,BS             },\
/* 336 */ { IX,BS             },\
/* 337 */ { LS,LT             },\
/* 338 */ { ID                },\
/* 339 */ { LS,LT             },\
/* 340 */ { ID                } \
}

#define post_render_scanline {\
/* 000 */ { ID                } \
}

#define special_post_render_scanline {\
/* 000 */ { ID                },\
/* 001 */ { SV                } \
}

void (*events[262][342][max_events])(struct ppu *) = {
/* 000 */  visible_scanline,
/* 001 */  visible_scanline,
/* 002 */  visible_scanline,
/* 003 */  visible_scanline,
/* 004 */  visible_scanline,
/* 005 */  visible_scanline,
/* 006 */  visible_scanline,
/* 007 */  visible_scanline,
/* 008 */  visible_scanline,
/* 009 */  visible_scanline,
/* 010 */  visible_scanline,
/* 011 */  visible_scanline,
/* 012 */  visible_scanline,
/* 013 */  visible_scanline,
/* 014 */  visible_scanline,
/* 015 */  visible_scanline,
/* 016 */  visible_scanline,
/* 017 */  visible_scanline,
/* 018 */  visible_scanline,
/* 019 */  visible_scanline,
/* 020 */  visible_scanline,
/* 021 */  visible_scanline,
/* 022 */  visible_scanline,
/* 023 */  visible_scanline,
/* 024 */  visible_scanline,
/* 025 */  visible_scanline,
/* 026 */  visible_scanline,
/* 027 */  visible_scanline,
/* 028 */  visible_scanline,
/* 029 */  visible_scanline,
/* 030 */  visible_scanline,
/* 031 */  visible_scanline,
/* 032 */  visible_scanline,
/* 033 */  visible_scanline,
/* 034 */  visible_scanline,
/* 035 */  visible_scanline,
/* 036 */  visible_scanline,
/* 037 */  visible_scanline,
/* 038 */  visible_scanline,
/* 039 */  visible_scanline,
/* 040 */  visible_scanline,
/* 041 */  visible_scanline,
/* 042 */  visible_scanline,
/* 043 */  visible_scanline,
/* 044 */  visible_scanline,
/* 045 */  visible_scanline,
/* 046 */  visible_scanline,
/* 047 */  visible_scanline,
/* 048 */  visible_scanline,
/* 049 */  visible_scanline,
/* 050 */  visible_scanline,
/* 051 */  visible_scanline,
/* 052 */  visible_scanline,
/* 053 */  visible_scanline,
/* 054 */  visible_scanline,
/* 055 */  visible_scanline,
/* 056 */  visible_scanline,
/* 057 */  visible_scanline,
/* 058 */  visible_scanline,
/* 059 */  visible_scanline,
/* 060 */  visible_scanline,
/* 061 */  visible_scanline,
/* 062 */  visible_scanline,
/* 063 */  visible_scanline,
/* 064 */  visible_scanline,
/* 065 */  visible_scanline,
/* 066 */  visible_scanline,
/* 067 */  visible_scanline,
/* 068 */  visible_scanline,
/* 069 */  visible_scanline,
/* 070 */  visible_scanline,
/* 071 */  visible_scanline,
/* 072 */  visible_scanline,
/* 073 */  visible_scanline,
/* 074 */  visible_scanline,
/* 075 */  visible_scanline,
/* 076 */  visible_scanline,
/* 077 */  visible_scanline,
/* 078 */  visible_scanline,
/* 079 */  visible_scanline,
/* 080 */  visible_scanline,
/* 081 */  visible_scanline,
/* 082 */  visible_scanline,
/* 083 */  visible_scanline,
/* 084 */  visible_scanline,
/* 085 */  visible_scanline,
/* 086 */  visible_scanline,
/* 087 */  visible_scanline,
/* 088 */  visible_scanline,
/* 089 */  visible_scanline,
/* 090 */  visible_scanline,
/* 091 */  visible_scanline,
/* 092 */  visible_scanline,
/* 093 */  visible_scanline,
/* 094 */  visible_scanline,
/* 095 */  visible_scanline,
/* 096 */  visible_scanline,
/* 097 */  visible_scanline,
/* 098 */  visible_scanline,
/* 099 */  visible_scanline,
/* 100 */  visible_scanline,
/* 101 */  visible_scanline,
/* 102 */  visible_scanline,
/* 103 */  visible_scanline,
/* 104 */  visible_scanline,
/* 105 */  visible_scanline,
/* 106 */  visible_scanline,
/* 107 */  visible_scanline,
/* 108 */  visible_scanline,
/* 109 */  visible_scanline,
/* 110 */  visible_scanline,
/* 111 */  visible_scanline,
/* 112 */  visible_scanline,
/* 113 */  visible_scanline,
/* 114 */  visible_scanline,
/* 115 */  visible_scanline,
/* 116 */  visible_scanline,
/* 117 */  visible_scanline,
/* 118 */  visible_scanline,
/* 119 */  visible_scanline,
/* 120 */  visible_scanline,
/* 121 */  visible_scanline,
/* 122 */  visible_scanline,
/* 123 */  visible_scanline,
/* 124 */  visible_scanline,
/* 125 */  visible_scanline,
/* 126 */  visible_scanline,
/* 127 */  visible_scanline,
/* 128 */  visible_scanline,
/* 129 */  visible_scanline,
/* 130 */  visible_scanline,
/* 131 */  visible_scanline,
/* 132 */  visible_scanline,
/* 133 */  visible_scanline,
/* 134 */  visible_scanline,
/* 135 */  visible_scanline,
/* 136 */  visible_scanline,
/* 137 */  visible_scanline,
/* 138 */  visible_scanline,
/* 139 */  visible_scanline,
/* 140 */  visible_scanline,
/* 141 */  visible_scanline,
/* 142 */  visible_scanline,
/* 143 */  visible_scanline,
/* 144 */  visible_scanline,
/* 145 */  visible_scanline,
/* 146 */  visible_scanline,
/* 147 */  visible_scanline,
/* 148 */  visible_scanline,
/* 149 */  visible_scanline,
/* 150 */  visible_scanline,
/* 151 */  visible_scanline,
/* 152 */  visible_scanline,
/* 153 */  visible_scanline,
/* 154 */  visible_scanline,
/* 155 */  visible_scanline,
/* 156 */  visible_scanline,
/* 157 */  visible_scanline,
/* 158 */  visible_scanline,
/* 159 */  visible_scanline,
/* 160 */  visible_scanline,
/* 161 */  visible_scanline,
/* 162 */  visible_scanline,
/* 163 */  visible_scanline,
/* 164 */  visible_scanline,
/* 165 */  visible_scanline,
/* 166 */  visible_scanline,
/* 167 */  visible_scanline,
/* 168 */  visible_scanline,
/* 169 */  visible_scanline,
/* 170 */  visible_scanline,
/* 171 */  visible_scanline,
/* 172 */  visible_scanline,
/* 173 */  visible_scanline,
/* 174 */  visible_scanline,
/* 175 */  visible_scanline,
/* 176 */  visible_scanline,
/* 177 */  visible_scanline,
/* 178 */  visible_scanline,
/* 179 */  visible_scanline,
/* 180 */  visible_scanline,
/* 181 */  visible_scanline,
/* 182 */  visible_scanline,
/* 183 */  visible_scanline,
/* 184 */  visible_scanline,
/* 185 */  visible_scanline,
/* 186 */  visible_scanline,
/* 187 */  visible_scanline,
/* 188 */  visible_scanline,
/* 189 */  visible_scanline,
/* 190 */  visible_scanline,
/* 191 */  visible_scanline,
/* 192 */  visible_scanline,
/* 193 */  visible_scanline,
/* 194 */  visible_scanline,
/* 195 */  visible_scanline,
/* 196 */  visible_scanline,
/* 197 */  visible_scanline,
/* 198 */  visible_scanline,
/* 199 */  visible_scanline,
/* 200 */  visible_scanline,
/* 201 */  visible_scanline,
/* 202 */  visible_scanline,
/* 203 */  visible_scanline,
/* 204 */  visible_scanline,
/* 205 */  visible_scanline,
/* 206 */  visible_scanline,
/* 207 */  visible_scanline,
/* 208 */  visible_scanline,
/* 209 */  visible_scanline,
/* 210 */  visible_scanline,
/* 211 */  visible_scanline,
/* 212 */  visible_scanline,
/* 213 */  visible_scanline,
/* 214 */  visible_scanline,
/* 215 */  visible_scanline,
/* 216 */  visible_scanline,
/* 217 */  visible_scanline,
/* 218 */  visible_scanline,
/* 219 */  visible_scanline,
/* 220 */  visible_scanline,
/* 221 */  visible_scanline,
/* 222 */  visible_scanline,
/* 223 */  visible_scanline,
/* 224 */  visible_scanline,
/* 225 */  visible_scanline,
/* 226 */  visible_scanline,
/* 227 */  visible_scanline,
/* 228 */  visible_scanline,
/* 229 */  visible_scanline,
/* 230 */  visible_scanline,
/* 231 */  visible_scanline,
/* 232 */  visible_scanline,
/* 233 */  visible_scanline,
/* 234 */  visible_scanline,
/* 235 */  visible_scanline,
/* 236 */  visible_scanline,
/* 237 */  visible_scanline,
/* 238 */  visible_scanline,
/* 239 */  visible_scanline,
/* 240 */  post_render_scanline,
/* 241 */  special_post_render_scanline,
/* 242 */  post_render_scanline,
/* 243 */  post_render_scanline,
/* 244 */  post_render_scanline,
/* 245 */  post_render_scanline,
/* 246 */  post_render_scanline,
/* 247 */  post_render_scanline,
/* 248 */  post_render_scanline,
/* 249 */  post_render_scanline,
/* 250 */  post_render_scanline,
/* 251 */  post_render_scanline,
/* 252 */  post_render_scanline,
/* 253 */  post_render_scanline,
/* 254 */  post_render_scanline,
/* 255 */  post_render_scanline,
/* 256 */  post_render_scanline,
/* 257 */  post_render_scanline,
/* 258 */  post_render_scanline,
/* 259 */  post_render_scanline,
/* 260 */  post_render_scanline,
/* 261 */  pre_render_scanline
};