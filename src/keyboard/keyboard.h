#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

enum key {
	key_a = 0,
	key_d,
	key_e,
	key_f,
	key_g,
	key_i,
	key_j,
	key_k,
	key_l,
	key_o,
	key_q,
	key_s,
	key_u,
	key_w,
	key_semicolon,
	key_apostrophe,
	key_escape,
	max_keys
};

struct keyboard;

struct keyboard *keyboard_new(void);
bool keyboard_pressed(struct keyboard *keyboard, enum key key);
void keyboard_destroy(struct keyboard *keyboard);

#endif