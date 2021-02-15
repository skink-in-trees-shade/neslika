#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdlib.h>
#include "platform/screen.h"

struct screen {
	int width;
	int height;
	Display *display;
	Window window;
	GLXContext context;
	GLuint texture;
	uint32_t *pixels;
};

struct screen *screen_new(char *title, int width, int height) {
	struct screen *screen = calloc(1, sizeof(struct screen));
	screen->width = width;
	screen->height = height;
	screen->pixels = calloc(screen->width * screen->height, sizeof(uint32_t));

	screen->display = XOpenDisplay(NULL);
	screen->window = XCreateSimpleWindow(screen->display, DefaultRootWindow(screen->display), 0, 0, screen->width * 2, screen->height * 2, 0, 0, 0);
	XStoreName(screen->display, screen->window, title);

	Atom window_type = XInternAtom(screen->display, "_NET_WM_WINDOW_TYPE", False);
	Atom dialog_type = XInternAtom(screen->display, "_NET_WM_WINDOW_TYPE_DIALOG", False);
	XChangeProperty(screen->display, screen->window, window_type, XA_ATOM, 32, PropModeReplace, (unsigned char*)&dialog_type, 1);

	XMapWindow(screen->display, screen->window);

	GLint visual_attributes[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
	XVisualInfo *visual_info = glXChooseVisual(screen->display, 0, visual_attributes);
	screen->context = glXCreateContext(screen->display, visual_info, NULL, GL_TRUE);
	glXMakeCurrent(screen->display, screen->window, screen->context);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &screen->texture);
	glBindTexture(GL_TEXTURE_2D, screen->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screen->width, screen->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	screen->pixels[screen->width * y + x] = 0xFF000000 | (r << 16) | (g << 8) | b;

	if (x == screen->width - 1 && y == screen->height - 1) {
		screen_update(screen);
	}
}

void screen_update(struct screen *screen) {
	glBindTexture(GL_TEXTURE_2D, screen->texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, screen->width, screen->height, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)screen->pixels);

	glBegin(GL_QUADS);
		glTexCoord2d(0.0, 0.0);
		glVertex2d(-1.0, 1.0);

		glTexCoord2d(1.0, 0.0);
		glVertex2d(1.0, 1.0);

		glTexCoord2d(1.0, 1.0);
		glVertex2d(1.0, -1.0);

		glTexCoord2d(0.0, 1.0);
		glVertex2d(-1.0, -1.0);
	glEnd();
}

void screen_commit(struct screen *screen) {
	glXSwapBuffers(screen->display, screen->window);
}

void screen_destroy(struct screen *screen) {
	glDeleteTextures(1, &screen->texture);
	glXMakeCurrent(screen->display, None, NULL);
	glXDestroyContext(screen->display, screen->context);
	XDestroyWindow(screen->display, screen->window);
	XCloseDisplay(screen->display);
	free(screen->pixels);
	free(screen);
}