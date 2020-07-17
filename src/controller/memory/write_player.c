#include "controller/controller.h"
#include "write_player.h"

enum keyboard {
	keyboard_a = 65,
	keyboard_d = 68,
	keyboard_e = 69,
	keyboard_f = 70,
	keyboard_g = 71,
	keyboard_i = 73,
	keyboard_j = 74,
	keyboard_k = 75,
	keyboard_l = 76,
	keyboard_o = 79,
	keyboard_q = 81,
	keyboard_s = 83,
	keyboard_u = 85,
	keyboard_w = 87,
	keyboard_semicolon = 59,
	keyboard_apostrophe = 39
};

static uint8_t get_player_one(struct controller *controller) {
	return 0
		| (screen_key_pressed(controller->screen, keyboard_f) << 0)
		| (screen_key_pressed(controller->screen, keyboard_g) << 1)
		| (screen_key_pressed(controller->screen, keyboard_q) << 2)
		| (screen_key_pressed(controller->screen, keyboard_e) << 3)
		| (screen_key_pressed(controller->screen, keyboard_w) << 4)
		| (screen_key_pressed(controller->screen, keyboard_s) << 5)
		| (screen_key_pressed(controller->screen, keyboard_a) << 6)
		| (screen_key_pressed(controller->screen, keyboard_d) << 7);
}

static uint8_t get_player_two(struct controller *controller) {
	return 0
		| (screen_key_pressed(controller->screen, keyboard_semicolon) << 0)
		| (screen_key_pressed(controller->screen, keyboard_apostrophe) << 1)
		| (screen_key_pressed(controller->screen, keyboard_u) << 2)
		| (screen_key_pressed(controller->screen, keyboard_o) << 3)
		| (screen_key_pressed(controller->screen, keyboard_i) << 4)
		| (screen_key_pressed(controller->screen, keyboard_k) << 5)
		| (screen_key_pressed(controller->screen, keyboard_j) << 6)
		| (screen_key_pressed(controller->screen, keyboard_l) << 7);
}

void write_player(void *device, uint16_t address, uint8_t value) {
	(void)address;

	struct controller *controller = device;
	controller->write_toggle = value & 0x01;
	if (controller->write_toggle) {
		controller->player_one = get_player_one(controller);
		controller->player_two = get_player_two(controller);
	}
}