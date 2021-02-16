#define WIN32_LEAN_AND_MEAN
#undef UNICODE
#include <windows.h>
#include <stdlib.h>
#include "platform/screen.h"

struct screen {
	int width;
	int height;
	HWND hWnd;
	HBITMAP hBitmap;
	DWORD *pixels;
};

struct screen *screen_new(char *title, int width, int height) {
	struct screen *screen = calloc(1, sizeof(struct screen));
	screen->width = width;
	screen->height = height;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS wc = {0};
	wc.lpfnWndProc = &DefWindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = title;
	RegisterClass(&wc);

	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	RECT r = { 0, 0, screen->width * 2, screen->height * 2 };
	AdjustWindowRect(&r, dwStyle, FALSE);
	screen->hWnd = CreateWindow(title, title, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL);

	HDC hDc = GetDC(screen->hWnd);
	HDC hDcMem = CreateCompatibleDC(hDc);

	BITMAPINFO bmi;
	ZeroMemory(&bmi,sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = screen->width;
	bmi.bmiHeader.biHeight = -screen->height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;

	screen->hBitmap = CreateDIBSection(hDc, &bmi, DIB_RGB_COLORS, (void **)&screen->pixels, NULL, 0);

	DeleteDC(hDcMem);
	ReleaseDC(screen->hWnd, hDc);

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	screen->pixels[screen->width * y + x] = (b << 16) | (g << 8) | r;

	if (x == screen->width - 1 && y == screen->height - 1) {
		screen_update(screen);
	}
}

void screen_update(struct screen *screen) {
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void screen_commit(struct screen *screen) {
	HDC hDc = GetDC(screen->hWnd);
	HDC hDcMem = CreateCompatibleDC(hDc);
	HBITMAP hOldBitmap = SelectObject(hDcMem, screen->hBitmap);

	StretchBlt(hDc, 0, 0, screen->width * 2, screen->height * 2, hDcMem, 0, 0, screen->width, screen->height, SRCCOPY);

	SelectObject(hDcMem, hOldBitmap);
	DeleteDC(hDcMem);
	ReleaseDC(screen->hWnd, hDc);
}

void screen_destroy(struct screen *screen) {
	DeleteObject(screen->hBitmap);
	DestroyWindow(screen->hWnd);
	free(screen);
}