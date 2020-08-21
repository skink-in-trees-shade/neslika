#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include "platform/keyboard.h"

static KeySym map[max_keys]= {
	[key_o] = XK_O,
	[key_p] = XK_P,
	[key_x] = XK_X,
	[key_z] = XK_Z,
	[key_num4] = XK_KP_4,
	[key_num5] = XK_KP_5,
	[key_num6] = XK_KP_6,
	[key_num8] = XK_KP_8,
	[key_left] = XK_Left,
	[key_right] = XK_Right,
	[key_up] = XK_Up,
	[key_down] = XK_Down,
	[key_tab] = XK_Tab,
	[key_space] = XK_space,
	[key_enter] = XK_Return,
	[key_backspace] = XK_BackSpace,
	[key_escape] = XK_Escape
};

struct keyboard {
	Display *display;
};

struct keyboard *keyboard_new(void) {
	struct keyboard *keyboard = calloc(1, sizeof(struct keyboard));
	keyboard->display = XOpenDisplay(NULL);
	return keyboard;
}

bool keyboard_pressed(struct keyboard *keyboard, enum key key) {
	char keys[32];
	XQueryKeymap(keyboard->display, keys);

	KeyCode code = XKeysymToKeycode(keyboard->display, map[key]);
	return keys[code / 8] & (1 << (code % 8));
}

void keyboard_destroy(struct keyboard *keyboard) {
	XCloseDisplay(keyboard->display);
	free(keyboard);
}