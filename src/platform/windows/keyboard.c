#include <windows.h>
#include <stdlib.h>
#include "platform/keyboard.h"

static int map[max_keys]= {
	[key_a] = 'A',
	[key_d] = 'D',
	[key_e] = 'E',
	[key_f] = 'F',
	[key_g] = 'G',
	[key_i] = 'I',
	[key_j] = 'J',
	[key_k] = 'K',
	[key_l] = 'L',
	[key_o] = 'O',
	[key_q] = 'Q',
	[key_s] = 'S',
	[key_u] = 'U',
	[key_w] = 'W',
	[key_semicolon] = VK_OEM_1,
	[key_apostrophe] = VK_OEM_7,
	[key_escape] = VK_ESCAPE
};

struct keyboard {
	int dummy;
};

struct keyboard *keyboard_new(void) {
	struct keyboard *keyboard = calloc(1, sizeof(struct keyboard));
	return keyboard;
}

bool keyboard_pressed(struct keyboard *keyboard, enum key key) {
	(void)keyboard;
	return GetAsyncKeyState(map[key]) & 0x8000;
}

void keyboard_destroy(struct keyboard *keyboard) {
	free(keyboard);
}