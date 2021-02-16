#include "neslika.h"

int main(int argc, char *argv[]) {
	struct neslika *nes = neslika_new();
	neslika_load(nes, "../robocop-3.nes");
	neslika_run(nes);
	neslika_destroy(nes);
	return 0;
}