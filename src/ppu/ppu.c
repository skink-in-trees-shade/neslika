#include <stdlib.h>
#include "memory/read_data.h"
#include "memory/read_name_table.h"
#include "memory/read_oam_data.h"
#include "memory/read_palette_table.h"
#include "memory/read_status.h"
#include "memory/write_address.h"
#include "memory/write_controller.h"
#include "memory/write_data.h"
#include "memory/write_mask.h"
#include "memory/write_name_table.h"
#include "memory/write_oam_address.h"
#include "memory/write_oam_data.h"
#include "memory/write_palette_table.h"
#include "memory/write_scroll.h"
#include "event.h"
#include "ppu.h"

struct ppu *ppu_new(struct bus *cpu_bus, struct bus *ppu_bus, struct screen *screen) {
	struct ppu *ppu = calloc(1, sizeof(struct ppu));
	ppu->name_table = calloc(0x800, sizeof(uint8_t));
	ppu->palette_table = calloc(0x20, sizeof(uint8_t));
	ppu->primary_oam = calloc(0x100, sizeof(uint8_t));
	ppu->secondary_oam = calloc(0x20, sizeof(uint8_t));
	ppu->status = 0xA0;
	ppu->scanline = 261;

	ppu->cpu_bus = cpu_bus;
	ppu->ppu_bus = ppu_bus;
	ppu->screen = screen;

	for (uint16_t i = 0x2000; i <= 0x3FFF; i += 8) {
		bus_register(ppu->cpu_bus, ppu, i + 0, i + 0, NULL, &write_controller);
		bus_register(ppu->cpu_bus, ppu, i + 1, i + 1, NULL, &write_mask);
		bus_register(ppu->cpu_bus, ppu, i + 2, i + 2, &read_status, NULL);
		bus_register(ppu->cpu_bus, ppu, i + 3, i + 3, NULL, &write_oam_address);
		bus_register(ppu->cpu_bus, ppu, i + 4, i + 4, &read_oam_data, &write_oam_data);
		bus_register(ppu->cpu_bus, ppu, i + 5, i + 5, NULL, &write_scroll);
		bus_register(ppu->cpu_bus, ppu, i + 6, i + 6, NULL, &write_address);
		bus_register(ppu->cpu_bus, ppu, i + 7, i + 7, &read_data, &write_data);
	}
	bus_register(ppu->ppu_bus, ppu, 0x2000, 0x3EFF, &read_name_table, &write_name_table);
	bus_register(ppu->ppu_bus, ppu, 0x3F00, 0x3FFF, &read_palette_table, &write_palette_table);

	return ppu;
}

void ppu_tick(struct ppu *ppu) {
	event_execute(ppu);

	ppu->cycle++;
	if (ppu->cycle == 341) {
		ppu->cycle = 0;
		ppu->scanline++;
		if (ppu->scanline == 262) {
			ppu->scanline = 0;
		}
	}
}

void ppu_destroy(struct ppu *ppu) {
	free(ppu->secondary_oam);
	free(ppu->primary_oam);
	free(ppu->palette_table);
	free(ppu->name_table);
	free(ppu);
}