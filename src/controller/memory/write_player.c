#include "controller/controller.h"
#include "write_player.h"

static uint8_t get_player_one(struct controller *controller) {
	return 0
		| (keyboard_pressed(controller->keyboard, key_f) << 0)
		| (keyboard_pressed(controller->keyboard, key_g) << 1)
		| (keyboard_pressed(controller->keyboard, key_q) << 2)
		| (keyboard_pressed(controller->keyboard, key_e) << 3)
		| (keyboard_pressed(controller->keyboard, key_w) << 4)
		| (keyboard_pressed(controller->keyboard, key_s) << 5)
		| (keyboard_pressed(controller->keyboard, key_a) << 6)
		| (keyboard_pressed(controller->keyboard, key_d) << 7);
}

static uint8_t get_player_two(struct controller *controller) {
	return 0
		| (keyboard_pressed(controller->keyboard, key_semicolon) << 0)
		| (keyboard_pressed(controller->keyboard, key_apostrophe) << 1)
		| (keyboard_pressed(controller->keyboard, key_u) << 2)
		| (keyboard_pressed(controller->keyboard, key_o) << 3)
		| (keyboard_pressed(controller->keyboard, key_i) << 4)
		| (keyboard_pressed(controller->keyboard, key_k) << 5)
		| (keyboard_pressed(controller->keyboard, key_j) << 6)
		| (keyboard_pressed(controller->keyboard, key_l) << 7);
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