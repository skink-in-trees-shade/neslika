#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include "keyboard.h"

static KeySym map[max_keys]= {
	[key_a] = XK_A,
	[key_d] = XK_D,
	[key_e] = XK_E,
	[key_f] = XK_F,
	[key_g] = XK_G,
	[key_i] = XK_I,
	[key_j] = XK_J,
	[key_k] = XK_K,
	[key_l] = XK_L,
	[key_o] = XK_O,
	[key_q] = XK_Q,
	[key_s] = XK_S,
	[key_u] = XK_U,
	[key_w] = XK_W,
	[key_semicolon] = XK_semicolon,
	[key_apostrophe] = XK_apostrophe,
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