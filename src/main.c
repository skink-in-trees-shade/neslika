#include "neslika.h"

int main(void) {
	struct neslika *nes = neslika_new();
	neslika_load(nes, "./assets/nestest.nes");
	neslika_run(nes);
	neslika_destroy(nes);
	return 0;
}