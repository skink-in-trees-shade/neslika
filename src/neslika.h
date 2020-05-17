#ifndef NESLIKA_H
#define NESLIKA_H

struct neslika;

struct neslika *neslika_new(void);
void neslika_load(struct neslika *nes, const char *filename);
void neslika_run(struct neslika *nes);
void neslika_destroy(struct neslika *nes);

#endif