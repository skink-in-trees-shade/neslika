#include "controller/controller.h"
#include "write_player.h"

static uint8_t get_player_one(struct controller *controller) {
	return 0
		| (keyboard_pressed(controller->keyboard, key_x) << 0)
		| (keyboard_pressed(controller->keyboard, key_z) << 1)
		| (keyboard_pressed(controller->keyboard, key_tab) << 2)
		| (keyboard_pressed(controller->keyboard, key_space) << 3)
		| (keyboard_pressed(controller->keyboard, key_up) << 4)
		| (keyboard_pressed(controller->keyboard, key_down) << 5)
		| (keyboard_pressed(controller->keyboard, key_left) << 6)
		| (keyboard_pressed(controller->keyboard, key_right) << 7);
}

static uint8_t get_player_two(struct controller *controller) {
	return 0
		| (keyboard_pressed(controller->keyboard, key_p) << 0)
		| (keyboard_pressed(controller->keyboard, key_o) << 1)
		| (keyboard_pressed(controller->keyboard, key_backspace) << 2)
		| (keyboard_pressed(controller->keyboard, key_enter) << 3)
		| (keyboard_pressed(controller->keyboard, key_num8) << 4)
		| (keyboard_pressed(controller->keyboard, key_num5) << 5)
		| (keyboard_pressed(controller->keyboard, key_num4) << 6)
		| (keyboard_pressed(controller->keyboard, key_num6) << 7);
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