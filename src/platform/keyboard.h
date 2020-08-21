#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

enum key {
	key_o,
	key_p,
	key_x,
	key_z,
	key_num4,
	key_num5,
	key_num6,
	key_num8,
	key_left,
	key_right,
	key_up,
	key_down,
	key_tab,
	key_space,
	key_enter,
	key_backspace,
	key_escape,
	max_keys
};

struct keyboard;

struct keyboard *keyboard_new(void);
bool keyboard_pressed(struct keyboard *keyboard, enum key key);
void keyboard_destroy(struct keyboard *keyboard);

#endif