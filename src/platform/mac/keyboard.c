#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>
#include <stdlib.h>
#include "platform/keyboard.h"

static CGKeyCode map[max_keys]= {
	[key_o] = kVK_ANSI_O,
	[key_p] = kVK_ANSI_P,
	[key_x] = kVK_ANSI_X,
	[key_z] = kVK_ANSI_Z,
	[key_num4] = kVK_ANSI_Keypad4,
	[key_num5] = kVK_ANSI_Keypad5,
	[key_num6] = kVK_ANSI_Keypad6,
	[key_num8] = kVK_ANSI_Keypad8,
	[key_left] = kVK_LeftArrow,
	[key_right] = kVK_RightArrow,
	[key_up] = kVK_UpArrow,
	[key_down] = kVK_DownArrow,
	[key_tab] = kVK_Tab,
	[key_space] = kVK_Space,
	[key_enter] = kVK_Return,
	[key_backspace] = kVK_Delete,
	[key_escape] = kVK_Escape
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
	return CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, map[key]);
}

void keyboard_destroy(struct keyboard *keyboard) {
	free(keyboard);
}