#define WIN32_LEAN_AND_MEAN
#undef UNICODE
#include <windows.h>
#define D3D_DISABLE_9EX
#include <d3d9.h>
#include <stdlib.h>
#include "platform/screen.h"

struct screen {
	int width;
	int height;
	HWND hWnd;
	DWORD *pixels;
	IDirect3D9 *context;
	IDirect3DDevice9 *device;
	IDirect3DSurface9 *surface;
};

struct screen *screen_new(char *title, int width, int height) {
	struct screen *screen = calloc(1, sizeof(struct screen));
	screen->width = width;
	screen->height = height;
	screen->pixels = calloc(screen->width * screen->height, sizeof(DWORD));

	HINSTANCE hInstance = GetModuleHandle(NULL);

	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	RECT r = { 0, 0, screen->width * 2, screen->height * 2 };
	AdjustWindowRect(&r, dwStyle, FALSE);
	screen->hWnd = CreateWindow(WC_DIALOG, title, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL);

	screen->context = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS parameters = {0};
	parameters.hDeviceWindow = screen->hWnd;
	parameters.Windowed = TRUE;
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	IDirect3D9_CreateDevice(screen->context, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &screen->device);
	IDirect3DDevice9_CreateOffscreenPlainSurface(screen->device, screen->width, screen->height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &screen->surface, NULL);

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	screen->pixels[screen->width * y + x] = (b << 16) | (g << 8) | r;

	if (x == screen->width - 1 && y == screen->height - 1) {
		screen_update(screen);
	}
}

void screen_update(struct screen *screen) {
}

void screen_commit(struct screen *screen) {
	D3DLOCKED_RECT rect;
	IDirect3DSurface9_LockRect(screen->surface, &rect, NULL, 0);
	CopyMemory(rect.pBits, screen->pixels, screen->width * screen->height * sizeof(DWORD));
	IDirect3DSurface9_UnlockRect(screen->surface);

	IDirect3DSurface9 *back_buffer;
	IDirect3DDevice9_GetBackBuffer(screen->device, 0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer);
	IDirect3DDevice9_StretchRect(screen->device, screen->surface, NULL, back_buffer, NULL, D3DTEXF_POINT);
	IDirect3DSurface9_Release(back_buffer);

	IDirect3DDevice9_Present(screen->device, NULL, NULL, NULL, NULL);
}

void screen_destroy(struct screen *screen) {
	IDirect3DSurface9_Release(screen->surface);
	IDirect3DDevice9_Release(screen->device);
	IDirect3D9_Release(screen->context);
	DestroyWindow(screen->hWnd);
	free(screen->pixels);
	free(screen);
}