#include <SDL.h>
#include <stdlib.h>
#include "screen.h"

struct screen {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	int width;
	int height;
	uint8_t *pixels;
};

struct screen *screen_new(char *title, int width, int height) {
	struct screen *screen = calloc(1, sizeof(struct screen));
	screen->width = width;
	screen->height = height;
	screen->pixels = calloc(width * height * 4, sizeof(uint8_t));

	SDL_InitSubSystem(SDL_INIT_VIDEO);
	screen->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * 2, height * 2, 0);
	screen->renderer = SDL_CreateRenderer(screen->window, -1, 0);
	screen->texture = SDL_CreateTexture(screen->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	size_t offset = (y * screen->width + x) * 4;
	screen->pixels[offset + 0] = r;
	screen->pixels[offset + 1] = g;
	screen->pixels[offset + 2] = b;
	screen->pixels[offset + 3] = SDL_ALPHA_OPAQUE;
}

void screen_update(struct screen *screen) {
	SDL_UpdateTexture(screen->texture, NULL, screen->pixels, screen->width * 4);
	SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
	SDL_RenderPresent(screen->renderer);
	SDL_PumpEvents();
}

void screen_destroy(struct screen *screen) {
	SDL_DestroyTexture(screen->texture);
	SDL_DestroyRenderer(screen->renderer);
	SDL_DestroyWindow(screen->window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	free(screen->pixels);
	free(screen);
}