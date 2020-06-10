#include <stddef.h>
#include <stdlib.h>
#include "controller.h"

enum keyboard {
	keyboard_space = 32,
	keyboard_x = 88,
	keyboard_z = 90,
	keyboard_tab = 258,
	keyboard_right = 262,
	keyboard_left = 263,
	keyboard_down = 264,
	keyboard_up = 265
};

static uint8_t _controller_read(struct device *device, uint16_t address) {
	struct controller *controller = (struct controller *)((char *)device - offsetof(struct controller, device));
	
	if (address == 0x4016) {
		uint8_t value = controller->state & 0x01;
		controller->state >>= 1;
		return value;
	}

	return 0x00;
}

static void _controller_write(struct device *device, uint16_t address, uint8_t value) {
	struct controller *controller = (struct controller *)((char *)device - offsetof(struct controller, device));

	if (address == 0x4016) {
		controller->write_toggle = value & 0x01;
		if (controller->write_toggle) {
			controller->state = 0
				| (screen_key_pressed(controller->screen, keyboard_x) << 0)
				| (screen_key_pressed(controller->screen, keyboard_z) << 1)
				| (screen_key_pressed(controller->screen, keyboard_tab) << 2)
				| (screen_key_pressed(controller->screen, keyboard_space) << 3)
				| (screen_key_pressed(controller->screen, keyboard_up) << 4)
				| (screen_key_pressed(controller->screen, keyboard_down) << 5)
				| (screen_key_pressed(controller->screen, keyboard_left) << 6)
				| (screen_key_pressed(controller->screen, keyboard_right) << 7);
		}
	}
}

struct controller *controller_new(void) {
	struct controller *controller = calloc(1, sizeof(struct controller));
	controller->device.address_from = 0x4016;
	controller->device.address_to = 0x4016;
	controller->device.read = &_controller_read;
	controller->device.write = &_controller_write;
	return controller;
}

void controller_tick(struct controller *controller) {
	(void)controller;
}

void controller_destroy(struct controller *controller) {
	free(controller);
}