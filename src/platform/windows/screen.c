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

static DWORD palette[0x40] = {
	0x00545454, 0x00001E74, 0x00081090, 0x00300088, 0x00440064, 0x005C0030, 0x00540400, 0x003C1800,
	0x00202A00, 0x00083A00, 0x00004000, 0x00003C00, 0x0000323C, 0x00000000, 0x00000000, 0x00000000,
	0x00989698, 0x00084CC4, 0x003032EC, 0x005C1EE4, 0x008814B0, 0x00A01464, 0x00982220, 0x00783C00,
	0x00545A00, 0x00287200, 0x00087C00, 0x00007628, 0x00006678, 0x00000000, 0x00000000, 0x00000000,
	0x00ECEEEC, 0x004C9AEC, 0x00787CEC, 0x00B062EC, 0x00E454EC, 0x00EC58B4, 0x00EC6A64, 0x00D48820,
	0x00A0AA00, 0x0074C400, 0x004CD020, 0x0038CC6C, 0x0038B4CC, 0x003C3C3C, 0x00000000, 0x00000000,
	0x00ECEEEC, 0x00A8CCEC, 0x00BCBCEC, 0x00D4B2EC, 0x00ECAEEC, 0x00ECAED4, 0x00ECB4B0, 0x00E4C490,
	0x00CCD278, 0x00B4DE78, 0x00A8E290, 0x0098E2B4, 0x00A0D6E4, 0x00A0A2A0, 0x00000000, 0x00000000
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

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t color_id) {
	screen->pixels[screen->width * y + x] = palette[color_id];
}

void screen_update(struct screen *screen) {
	HDC hDc = GetDC(screen->hWnd);
	HDC hDcMem = CreateCompatibleDC(hDc);
	HBITMAP hOldBitmap = SelectObject(hDcMem, screen->hBitmap);

	StretchBlt(hDc, 0, 0, screen->width * 2, screen->height * 2, hDcMem, 0, 0, screen->width, screen->height, SRCCOPY);

	SelectObject(hDcMem, hOldBitmap);
	DeleteDC(hDcMem);
	ReleaseDC(screen->hWnd, hDc);

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void screen_destroy(struct screen *screen) {
	DeleteObject(screen->hBitmap);
	DestroyWindow(screen->hWnd);
	free(screen);
}