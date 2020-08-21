#include <windows.h>
#include <stdlib.h>
#include "platform/keyboard.h"

static int map[max_keys]= {
	[key_o] = 'O',
	[key_p] = 'P',
	[key_x] = 'X',
	[key_z] = 'Z',
	[key_num4] = VK_NUMPAD4,
	[key_num5] = VK_NUMPAD5,
	[key_num6] = VK_NUMPAD6,
	[key_num8] = VK_NUMPAD8,
	[key_left] = VK_LEFT,
	[key_right] = VK_RIGHT,
	[key_up] = VK_UP,
	[key_down] = VK_DOWN,
	[key_tab] = VK_TAB,
	[key_space] = VK_SPACE,
	[key_enter] = VK_RETURN,
	[key_backspace] = VK_BACK,
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