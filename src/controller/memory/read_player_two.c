#include "controller/controller.h"
#include "read_player_two.h"

uint8_t read_player_two(void *device, uint16_t address) {
	(void)address;

	struct controller *controller = device;
	uint8_t value = controller->player_two & 0x01;
	controller->player_two >>= 1;
	return value;
}