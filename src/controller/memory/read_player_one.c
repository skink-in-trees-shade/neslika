#include "controller/controller.h"
#include "read_player_one.h"

uint8_t read_player_one(void *device, uint16_t address) {
	(void)address;

	struct controller *controller = device;
	uint8_t value = 0x40 | (controller->player_one & 0x01);
	controller->player_one >>= 1;
	return value;
}