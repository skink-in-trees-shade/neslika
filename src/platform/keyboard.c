#include <SDL.h>
#include <stdlib.h>
#include "keyboard.h"

static SDL_Scancode map[max_keys]= {
	[key_o] = SDL_SCANCODE_O,
	[key_p] = SDL_SCANCODE_P,
	[key_x] = SDL_SCANCODE_X,
	[key_z] = SDL_SCANCODE_Z,
	[key_num4] = SDL_SCANCODE_KP_4,
	[key_num5] = SDL_SCANCODE_KP_5,
	[key_num6] = SDL_SCANCODE_KP_6,
	[key_num8] = SDL_SCANCODE_KP_8,
	[key_left] = SDL_SCANCODE_LEFT,
	[key_right] = SDL_SCANCODE_RIGHT,
	[key_up] = SDL_SCANCODE_UP,
	[key_down] = SDL_SCANCODE_DOWN,
	[key_tab] = SDL_SCANCODE_TAB,
	[key_space] = SDL_SCANCODE_SPACE,
	[key_enter] = SDL_SCANCODE_RETURN,
	[key_backspace] = SDL_SCANCODE_BACKSPACE,
	[key_escape] = SDL_SCANCODE_ESCAPE
};

struct keyboard {
	const Uint8 *state;
};

struct keyboard *keyboard_new(void) {
	struct keyboard *keyboard = calloc(1, sizeof(struct keyboard));

	SDL_InitSubSystem(SDL_INIT_EVENTS);
	keyboard->state = SDL_GetKeyboardState(NULL);

	return keyboard;
}

bool keyboard_pressed(struct keyboard *keyboard, enum key key) {
	return keyboard->state[map[key]];
}

void keyboard_destroy(struct keyboard *keyboard) {
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	free(keyboard);
}