#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d2d1.h>
#include <stdlib.h>
#include "platform/screen.h"

#undef INTERFACE
#define INTERFACE ID2D1Factory
DECLARE_INTERFACE_(ID2D1Factory, IUnknown) {
BEGIN_INTERFACE
	STDMETHOD(dummy_QueryInterface)(void);
	STDMETHOD(dummy_AddRef)(void);
	STDMETHOD_(ULONG, Release)(THIS);
	STDMETHOD(dummy_ReloadSystemMetrics)(void);
	STDMETHOD(dummy_GetDesktopDpi)(void);
	STDMETHOD(dummy_CreateRectangleGeometry)(void);
	STDMETHOD(dummy_CreateRoundedRectangleGeometry)(void);
	STDMETHOD(dummy_CreateEllipseGeometry)(void);
	STDMETHOD(dummy_CreateGeometryGroup)(void);
	STDMETHOD(dummy_CreateTransformedGeometry)(void);
	STDMETHOD(dummy_CreatePathGeometry)(void);
	STDMETHOD(dummy_CreateStrokeStyle)(void);
	STDMETHOD(dummy_CreateDrawingStateBlock)(void);
	STDMETHOD(dummy_CreateWicBitmapRenderTarget)(void);
	STDMETHOD(CreateHwndRenderTarget)(THIS, const D2D1_RENDER_TARGET_PROPERTIES *, const D2D1_HWND_RENDER_TARGET_PROPERTIES *, ID2D1HwndRenderTarget **);
END_INTERFACE
};
#undef INTERFACE
#define INTERFACE ID2D1HwndRenderTarget
DECLARE_INTERFACE_(ID2D1HwndRenderTarget, ID2D1RenderTarget) {
BEGIN_INTERFACE
	STDMETHOD(dummy_QueryInterface)(void);
	STDMETHOD(dummy_AddRef)(void);
	STDMETHOD_(ULONG, Release)(THIS);
	STDMETHOD(dummy_GetFactory)(void);
	STDMETHOD(CreateBitmap)(THIS, D2D1_SIZE_U, const void *, UINT32, const D2D1_BITMAP_PROPERTIES *, ID2D1Bitmap **);
	STDMETHOD(dummy_CreateBitmapFromWicBitmap)(void);
	STDMETHOD(dummy_CreateSharedBitmap)(void);
	STDMETHOD(dummy_CreateBitmapBrush)(void);
	STDMETHOD(dummy_CreateSolidColorBrush)(void);
	STDMETHOD(dummy_CreateGradientStopCollection)(void);
	STDMETHOD(dummy_CreateLinearGradientBrush)(void);
	STDMETHOD(dummy_CreateRadialGradientBrush)(void);
	STDMETHOD(dummy_CreateCompatibleRenderTarget)(void);
	STDMETHOD(dummy_CreateLayer)(void);
	STDMETHOD(dummy_CreateMesh)(void);
	STDMETHOD(dummy_DrawLine)(void);
	STDMETHOD(dummy_DrawRectangle)(void);
	STDMETHOD(dummy_FillRectangle)(void);
	STDMETHOD(dummy_DrawRoundedRectangle)(void);
	STDMETHOD(dummy_FillRoundedRectangle)(void);
	STDMETHOD(dummy_DrawEllipse)(void);
	STDMETHOD(dummy_FillEllipse)(void);
	STDMETHOD(dummy_DrawGeometry)(void);
	STDMETHOD(dummy_FillGeometry)(void);
	STDMETHOD(dummy_FillMesh)(void);
	STDMETHOD(dummy_FillOpacityMask)(void);
	STDMETHOD_(void, DrawBitmap)(THIS, ID2D1Bitmap *, const D2D1_RECT_F *, FLOAT, D2D1_BITMAP_INTERPOLATION_MODE, const D2D1_RECT_F *);
	STDMETHOD(dummy_DrawText)(void);
	STDMETHOD(dummy_DrawTextLayout)(void);
	STDMETHOD(dummy_DrawGlyphRun)(void);
	STDMETHOD(dummy_SetTransform)(void);
	STDMETHOD(dummy_GetTransform)(void);
	STDMETHOD(dummy_SetAntialiasMode)(void);
	STDMETHOD(dummy_GetAntialiasMode)(void);
	STDMETHOD(dummy_SetTextAntialiasMode)(void);
	STDMETHOD(dummy_GetTextAntialiasMode)(void);
	STDMETHOD(dummy_SetTextRenderingParams)(void);
	STDMETHOD(dummy_GetTextRenderingParams)(void);
	STDMETHOD(dummy_SetTags)(void);
	STDMETHOD(dummy_GetTags)(void);
	STDMETHOD(dummy_PushLayer)(void);
	STDMETHOD(dummy_PopLayer)(void);
	STDMETHOD(dummy_Flush)(void);
	STDMETHOD(dummy_SaveDrawingState)(void);
	STDMETHOD(dummy_RestoreDrawingState)(void);
	STDMETHOD(dummy_PushAxisAlignedClip)(void);
	STDMETHOD(dummy_PopAxisAlignedClip)(void);
	STDMETHOD(dummy_Clear)(void);
	STDMETHOD_(void, BeginDraw)(THIS);
	STDMETHOD(EndDraw)(THIS, D2D1_TAG *, D2D1_TAG *);
END_INTERFACE
};
#undef INTERFACE
#define INTERFACE ID2D1Bitmap
DECLARE_INTERFACE_(ID2D1Bitmap, ID2D1Image) {
BEGIN_INTERFACE
	STDMETHOD(dummy_QueryInterface)(void);
	STDMETHOD(dummy_AddRef)(void);
	STDMETHOD_(ULONG, Release)(THIS);
	STDMETHOD(dummy_GetFactory)(void);
	STDMETHOD(dummy_GetSize)(void);
	STDMETHOD(dummy_GetPixelSize)(void);
	STDMETHOD(dummy_GetPixelFormat)(void);
	STDMETHOD(dummy_GetDpi)(void);
	STDMETHOD(dummy_CopyFromBitmap)(void);
	STDMETHOD(dummy_CopyFromRenderTarget)(void);
	STDMETHOD(CopyFromMemory)(THIS, const D2D1_RECT_U *, const void *, UINT32);
END_INTERFACE
};

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
	screen->factory->lpVtbl->CreateHwndRenderTarget(screen->factory, &rtProp, &hrtProp, &screen->target);

	D2D1_SIZE_U bmpSize = { screen->width, screen->height };
	D2D1_BITMAP_PROPERTIES bmpProp = {0};
	bmpProp.pixelFormat = pf;
	screen->target->lpVtbl->CreateBitmap(screen->target, bmpSize, NULL, 0, &bmpProp, &screen->bitmap);

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	screen->pixels[screen->width * y + x] = (b << 16) | (g << 8) | r;
}

void screen_update(struct screen *screen) {
	screen->bitmap->lpVtbl->CopyFromMemory(screen->bitmap, NULL, screen->pixels, screen->width * sizeof(DWORD));

	screen->target->lpVtbl->BeginDraw(screen->target);

	D2D1_RECT_F rcDst = { 0, 0, screen->width * 2, screen->height * 2 };
	screen->target->lpVtbl->DrawBitmap(screen->target, screen->bitmap, &rcDst, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, NULL);

	screen->target->lpVtbl->EndDraw(screen->target, NULL, NULL);

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void screen_destroy(struct screen *screen) {
	screen->bitmap->lpVtbl->Release(screen->bitmap);
	screen->target->lpVtbl->Release(screen->target);
	screen->factory->lpVtbl->Release(screen->factory);
	DestroyWindow(screen->window);
	free(screen->pixels);
	free(screen);
}