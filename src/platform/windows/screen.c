#define WIN32_LEAN_AND_MEAN
#define INITGUID
#include <windows.h>
#include <d2d1.h>
#include <stdlib.h>
#include "platform/screen.h"

struct screen {
	int width;
	int height;
	HWND window;
	DWORD *pixels;
	ID2D1Factory *factory;
	ID2D1HwndRenderTarget *target;
	ID2D1Bitmap *bitmap;
};

struct screen *screen_new(char *title, int width, int height) {
	struct screen *screen = calloc(1, sizeof(struct screen));
	screen->width = width;
	screen->height = height;
	screen->pixels = calloc(screen->width * screen->height, sizeof(DWORD));

	HINSTANCE hInstance = GetModuleHandle(NULL);
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	RECT rcWnd = { 0, 0, screen->width * 2, screen->height * 2 };
	AdjustWindowRect(&rcWnd, dwStyle, FALSE);
	screen->window = CreateWindow(WC_DIALOG, title, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top, NULL, NULL, hInstance, NULL);

	D2D1_FACTORY_OPTIONS opt = {0};
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &IID_ID2D1Factory, &opt, (void **)&screen->factory);

	D2D1_PIXEL_FORMAT pf = { DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE };
	D2D1_RENDER_TARGET_PROPERTIES rtProp = {0};
	rtProp.pixelFormat = pf;
	D2D1_HWND_RENDER_TARGET_PROPERTIES hrtProp = {0};
	hrtProp.hwnd = screen->window;
	hrtProp.pixelSize = (D2D1_SIZE_U){ screen->width * 2, screen->height * 2 };
	ID2D1Factory_CreateHwndRenderTarget(screen->factory, &rtProp, &hrtProp, &screen->target);

	D2D1_SIZE_U bmpSize = { screen->width, screen->height };
	D2D1_BITMAP_PROPERTIES bmpProp = {0};
	bmpProp.pixelFormat = pf;
	ID2D1HwndRenderTarget_CreateBitmap(screen->target, bmpSize, NULL, 0, &bmpProp, &screen->bitmap);

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	screen->pixels[screen->width * y + x] = (b << 16) | (g << 8) | r;
}

void screen_update(struct screen *screen) {
	ID2D1Bitmap_CopyFromMemory(screen->bitmap, NULL, screen->pixels, screen->width * sizeof(DWORD));

	ID2D1HwndRenderTarget_BeginDraw(screen->target);

	D2D1_RECT_F rcDst = { 0, 0, screen->width * 2, screen->height * 2 };
	ID2D1HwndRenderTarget_DrawBitmap(screen->target, screen->bitmap, &rcDst, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, NULL);

	ID2D1HwndRenderTarget_EndDraw(screen->target, NULL, NULL);

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void screen_destroy(struct screen *screen) {
	ID2D1Bitmap_Release(screen->bitmap);
	ID2D1HwndRenderTarget_Release(screen->target);
	ID2D1Factory_Release(screen->factory);
	DestroyWindow(screen->window);
	free(screen->pixels);
	free(screen);
}