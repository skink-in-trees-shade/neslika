#include <stdlib.h>
#include "controller.h"

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

static uint8_t _controller_read_p1(void *device, uint16_t address) {
	(void)address;
	struct controller *controller = device;
	uint8_t value = controller->state_p1 & 0x01;
	controller->state_p1 >>= 1;
	return value;
}

static uint8_t _controller_read_p2(void *device, uint16_t address) {
	(void)address;
	struct controller *controller = device;
	uint8_t value = controller->state_p2 & 0x01;
	controller->state_p2 >>= 1;
	return value;
}

static void _controller_write(void *device, uint16_t address, uint8_t value) {
	(void)address;
	struct controller *controller = device;
	controller->write_toggle = value & 0x01;
	if (controller->write_toggle) {
		controller->state_p1 = 0
			| (screen_key_pressed(controller->screen, keyboard_f) << 0)
			| (screen_key_pressed(controller->screen, keyboard_g) << 1)
			| (screen_key_pressed(controller->screen, keyboard_q) << 2)
			| (screen_key_pressed(controller->screen, keyboard_e) << 3)
			| (screen_key_pressed(controller->screen, keyboard_w) << 4)
			| (screen_key_pressed(controller->screen, keyboard_s) << 5)
			| (screen_key_pressed(controller->screen, keyboard_a) << 6)
			| (screen_key_pressed(controller->screen, keyboard_d) << 7);
		controller->state_p2 = 0
			| (screen_key_pressed(controller->screen, keyboard_semicolon) << 0)
			| (screen_key_pressed(controller->screen, keyboard_apostrophe) << 1)
			| (screen_key_pressed(controller->screen, keyboard_u) << 2)
			| (screen_key_pressed(controller->screen, keyboard_o) << 3)
			| (screen_key_pressed(controller->screen, keyboard_i) << 4)
			| (screen_key_pressed(controller->screen, keyboard_k) << 5)
			| (screen_key_pressed(controller->screen, keyboard_j) << 6)
			| (screen_key_pressed(controller->screen, keyboard_l) << 7);
	}
}

struct controller *controller_new(struct bus *bus) {
	struct controller *controller = calloc(1, sizeof(struct controller));

	controller->bus = bus;

	bus_register(controller->bus, controller, 0x4016, 0x4016, &_controller_read_p1, &_controller_write);
	bus_register(controller->bus, controller, 0x4017, 0x4017, &_controller_read_p2, NULL);

	return controller;
}

void controller_tick(struct controller *controller) {
	(void)controller;
}

void controller_destroy(struct controller *controller) {
	free(controller);
}