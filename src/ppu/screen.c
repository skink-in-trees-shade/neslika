#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "screen.h"

const int width = 256;
const int height = 240;

static uint32_t palette[0x40] = {
	0xFF545454, 0xFF741E00, 0xFF901008, 0xFF880030, 0xFF640044, 0xFF30005C, 0xFF000454, 0xFF00183C,
	0xFF002A20, 0xFF003A08, 0xFF004000, 0xFF003C00, 0xFF3C3200, 0xFF000000, 0xFF000000, 0xFF000000,
	0xFF989698, 0xFFC44C08, 0xFFEC3230, 0xFFE41E5C, 0xFFB01488, 0xFF6414A0, 0xFF202298, 0xFF003C78,
	0xFF005A54, 0xFF007228, 0xFF007C08, 0xFF287600, 0xFF786600, 0xFF000000, 0xFF000000, 0xFF000000,
	0xFFECEEEC, 0xFFEC9A4C, 0xFFEC7C78, 0xFFEC62B0, 0xFFEC54E4, 0xFFB458EC, 0xFF646AEC, 0xFF2088D4,
	0xFF00AAA0, 0xFF00C474, 0xFF20D04C, 0xFF6CCC38, 0xFFCCB438, 0xFF3C3C3C, 0xFF000000, 0xFF000000,
	0xFFECEEEC, 0xFFECCCA8, 0xFFECBCBC, 0xFFECB2D4, 0xFFECAEEC, 0xFFD4AEEC, 0xFFB0B4EC, 0xFF90C4E4,
	0xFF78D2CC, 0xFF78DEB4, 0xFF90E2A8, 0xFFB4E298, 0xFFE4D6A0, 0xFFA0A2A0, 0xFF000000, 0xFF000000
};

struct screen {
	GLFWwindow *window;
	GLuint texture;
	uint32_t *pixels;
};

struct screen *screen_new(void) {
	glfwInit();

	struct screen *screen = calloc(1, sizeof(struct screen));
	screen->pixels = calloc(width * height, sizeof(uint32_t));

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	screen->window = glfwCreateWindow(width * 2, height * 2, "Neslika", NULL, NULL);
	glfwMakeContextCurrent(screen->window);
	glfwSwapInterval(1);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &screen->texture);
	glBindTexture(GL_TEXTURE_2D, screen->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t color_id) {
	screen->pixels[width * y + x] = palette[color_id];
}

void screen_update(struct screen *screen) {
	glBindTexture(GL_TEXTURE_2D, screen->texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)screen->pixels);

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

	glfwSwapBuffers(screen->window);
	glfwPollEvents();
}

bool screen_done(struct screen *screen) {
	return glfwWindowShouldClose(screen->window);
}

void screen_destroy(struct screen *screen) {
	glDeleteTextures(1, &screen->texture);
	glfwDestroyWindow(screen->window);
	free(screen->pixels);
	free(screen);
	glfwTerminate();
}