#include <stddef.h>
#include <stdlib.h>
#include "event.h"
#include "ppu.h"

static uint8_t _ppu_cpu_read(struct device *device, uint16_t address) {
	struct ppu *ppu = (struct ppu *)((char *)device - offsetof(struct ppu, cpu_device));

	switch (address) {
		case 0x2002: {
			uint8_t value = (ppu->status & 0xE0) | (ppu->read_buffer & 0x1F);
			ppu->status |= 0x7F;
			ppu->write_toggle = false;
			return value;
		}
		break;

		case 0x2007: {
			uint8_t value = ppu->read_buffer;
			ppu->read_buffer = bus_read(ppu->bus, ppu->vram_address);
			if ((ppu->vram_address & 0x3F00) == 0x3F00) {
				value = ppu->read_buffer;
			}
			ppu->vram_address += (ppu->control & 0x04) == 0x04 ? 32 : 1;
			return value;
		}
		break;
	}

	return 0x00;
}

static void _ppu_cpu_write(struct device *device, uint16_t address, uint8_t value) {
	struct ppu *ppu = (struct ppu *)((char *)device - offsetof(struct ppu, cpu_device));

	switch (address) {
		case 0x2000:
			ppu->control = value;
			ppu->temp_vram_address = (ppu->temp_vram_address & 0x73FF) | ((value & 0x03) << 10);
		break;

		case 0x2001:
			ppu->mask = value;
		break;

		case 0x2005:
			if (!ppu->write_toggle) {
				ppu->fine_x = value & 0x07;
				ppu->temp_vram_address = (ppu->temp_vram_address & 0x7FE0) | (value >> 3);
			} else {
				ppu->temp_vram_address = (ppu->temp_vram_address & 0x0C1F) | ((value & 0x07) << 12) | ((value >> 3) << 5);
			}
			ppu->write_toggle = !ppu->write_toggle;
		break;

		case 0x2006:
			if (!ppu->write_toggle) {
				ppu->temp_vram_address = (ppu->temp_vram_address & 0x00FF) | ((value & 0x3F) << 8);
			} else {
				ppu->temp_vram_address = (ppu->temp_vram_address & 0xFF00) | value;
				ppu->vram_address = ppu->temp_vram_address;
			}
			ppu->write_toggle = !ppu->write_toggle;
		break;

		case 0x2007:
			bus_write(ppu->bus, ppu->vram_address, value);
			ppu->vram_address += (ppu->control & 0x04) == 0x04 ? 32 : 1;
		break;
	}
}

static uint8_t _ppu_ppu_read(struct device *device, uint16_t address) {
	struct ppu *ppu = (struct ppu *)((char *)device - offsetof(struct ppu, ppu_device));

	if (address >= 0x2000 && address <= 0x3EFF) {
		return ppu->name_table[address & 0x03FF];
	}

	if (address >= 0x3F00 && address <= 0x3FFF) {
		return ppu->palette_table[address & 0x001F];
	}

	return 0x00;
}

static void _ppu_ppu_write(struct device *device, uint16_t address, uint8_t value) {
	struct ppu *ppu = (struct ppu *)((char *)device - offsetof(struct ppu, ppu_device));

	if (address >= 0x2000 && address <= 0x3EFF) {
		ppu->name_table[address & 0x03FF] = value;
	}

	if (address >= 0x3F00 && address <= 0x3FFF) {
		ppu->palette_table[address & 0x001F] = value;
	}
}

struct ppu *ppu_new(void) {
	struct ppu *ppu = calloc(1, sizeof(struct ppu));
	ppu->name_table = calloc(0x0400, sizeof(uint8_t));
	ppu->palette_table = calloc(0x20, sizeof(uint8_t));
	ppu->status = 0xA0;
	ppu->scanline = 261;

	ppu->cpu_device.address_from = 0x2000;
	ppu->cpu_device.address_to = 0x2007;
	ppu->cpu_device.read = &_ppu_cpu_read;
	ppu->cpu_device.write = &_ppu_cpu_write;

	ppu->ppu_device.address_from = 0x2000;
	ppu->ppu_device.address_to = 0x3FFF;
	ppu->ppu_device.read = &_ppu_ppu_read;
	ppu->ppu_device.write = &_ppu_ppu_write;

	return ppu;
}

void ppu_tick(struct ppu *ppu) {
	void (**cycle_events)(struct ppu *) = events[ppu->scanline][ppu->cycle];
	for (int i = 0; i < 4 && cycle_events[i]; i++) {
		cycle_events[i](ppu);
	}

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
	free(ppu->palette_table);
	free(ppu->name_table);
	free(ppu);
}