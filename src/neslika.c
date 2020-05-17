#include <stdlib.h>
#include "bus.h"
#include "device.h"
#include "cpu/cpu.h"
#include "cartridge/ines.h"
#include "neslika.h"

struct neslika {
	struct bus *bus;
	struct cpu *cpu;
};

struct neslika *neslika_new(void) {
	struct neslika *nes = calloc(1, sizeof(struct neslika));

	nes->bus = bus_new();

	nes->cpu = cpu_new();
	nes->cpu->bus = nes->bus;
	bus_attach(nes->bus, (struct device *)nes->cpu);

	return nes;
}

void neslika_load(struct neslika *nes, const char *filename) {
	ines_load(nes->cpu, filename);
}

void neslika_run(struct neslika *nes) {
	do {
		cpu_fetch(nes->cpu);
		cpu_decode(nes->cpu);
		cpu_execute(nes->cpu);
	} while (cpu_running(nes->cpu));
}

void neslika_destroy(struct neslika *nes) {
	cpu_destroy(nes->cpu);
	bus_destroy(nes->bus);
	free(nes);
}