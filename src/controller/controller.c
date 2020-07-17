#include <stdlib.h>
#include "memory/read_player_one.h"
#include "memory/read_player_two.h"
#include "memory/write_player.h"
#include "controller.h"

struct controller *controller_new(struct bus *bus, struct keyboard *keyboard) {
	struct controller *controller = calloc(1, sizeof(struct controller));

	controller->bus = bus;
	controller->keyboard = keyboard;

	bus_register(controller->bus, controller, 0x4016, 0x4016, &read_player_one, &write_player);
	bus_register(controller->bus, controller, 0x4017, 0x4017, &read_player_two, NULL);

	return controller;
}

void controller_tick(struct controller *controller) {
	(void)controller;
}

void controller_destroy(struct controller *controller) {
	free(controller);
}