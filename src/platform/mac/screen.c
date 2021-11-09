#include <objc/message.h>
#include <objc/NSObjCRuntime.h>
#include <CoreGraphics/CoreGraphics.h>
#include <stdlib.h>
#include "platform/screen.h"

const char *shader = "\n\
	#include <metal_stdlib>\n\
	#include <simd/simd.h>\n\
	\n\
	using namespace metal;\n\
	\n\
	typedef struct {\n\
		float4 position [[position]];\n\
		float2 texture;\n\
	} Vertex;\n\
	\n\
	vertex Vertex compute(uint id [[vertex_id]]) {\n\
		float4x4 position = float4x4(\n\
			float4(-1.0, -1.0, 0.0, 1.0),\n\
			float4( 1.0, -1.0, 0.0, 1.0),\n\
			float4(-1.0,  1.0, 0.0, 1.0),\n\
			float4( 1.0,  1.0, 0.0, 1.0)\n\
		);\n\
		Vertex out;\n\
		out.position = position[id];\n\
		out.texture = position[id].xy * float2(0.5, -0.5) + 0.5;\n\
		return out;\n\
	}\n\
	\n\
	fragment float4 sample(Vertex in [[stage_in]], texture2d<float> texture [[texture(0)]]) {\n\
		constexpr sampler sampler(mag_filter::nearest, min_filter::nearest);\n\
		return texture.sample(sampler, in.texture);\n\
	}";

#define object_senda(obj, mtd) ((id (*)(id, SEL))objc_msgSend)((obj), sel_getUid(mtd))
#define class_senda(cls, mtd) ((id (*)(Class, SEL))objc_msgSend)(objc_getClass(cls), sel_getUid(mtd))
#define object_send(obj, mtd, ...) ((id (*)(id, SEL, ...))objc_msgSend)((obj), sel_getUid(mtd), __VA_ARGS__)
#define class_send(cls, mtd, ...) ((id (*)(Class, SEL, ...))objc_msgSend)(objc_getClass(cls), sel_getUid(mtd), __VA_ARGS__)

#define NSString_stringWithUTF8String(str) class_send("NSString", "stringWithUTF8String:", str)
#define NSDate_distantPast() class_senda("NSDate", "distantPast")
#define NSAutoreleasePool_alloc() class_senda("NSAutoreleasePool", "alloc")
#define NSAutoreleasePool_init(id) object_senda(id, "init")
#define NSAutoreleasePool_drain(id) object_senda(id, "drain")
#define NSApplication_sharedApplication() class_senda("NSApplication", "sharedApplication")
#define NSApplication_autorelease(id) object_senda(id, "autorelease")
#define NSApplication_setActivationPolicy(id, policy) object_send(id, "setActivationPolicy:", policy)
#define NSApplication_activateIgnoringOtherApps(id, activate) object_send(id, "activateIgnoringOtherApps:", activate)
#define NSApplication_nextEventMatchingMask(id, mask, until, mode, dequeue) object_send(id, "nextEventMatchingMask:untilDate:inMode:dequeue:", mask, until, mode, dequeue)
#define NSApplication_sendEvent(id, event) object_send(id, "sendEvent:", event)
#define NSApplication_updateWindows(id) object_senda(id, "updateWindows")
#define NSWindow_alloc() class_senda("NSWindow", "alloc")
#define NSWindow_initWithContentRect(id, rect, styleMask, backing, defer) object_send(id, "initWithContentRect:styleMask:backing:defer:", rect, styleMask, backing, defer)
#define NSWindow_autorelease(id) object_senda(id, "autorelease")
#define NSWindow_center(id) object_senda(id, "center")
#define NSWindow_setTitle(id, title) object_send(id, "setTitle:", NSString_stringWithUTF8String(title))
#define NSWindow_makeKeyAndOrderFront(id) object_send(id, "makeKeyAndOrderFront:", nil)
#define NSWindow_contentView(id) object_senda(id, "contentView")
#define NSView_setLayer(id, layer) object_send(id, "setLayer:", layer)
#define CAMetalLayer_layer() class_senda("CAMetalLayer", "layer")
#define CAMetalLayer_autorelease(id) object_senda(id, "autorelease")
#define CAMetalLayer_setDevice(id, device) object_send(id, "setDevice:", device)
#define CAMetalLayer_nextDrawable(id) object_senda(id, "nextDrawable")
#define MTLDevice_autorelease(id) object_senda(id, "autorelease")
#define MTLDevice_newLibraryWithSource(id, source) object_send(id, "newLibraryWithSource:options:error:", NSString_stringWithUTF8String(source), nil, nil)
#define MTLDevice_newRenderPipelineStateWithDescriptor(id, desc) object_send(id, "newRenderPipelineStateWithDescriptor:error:", desc, nil)
#define MTLDevice_newCommandQueue(id) object_senda(id, "newCommandQueue")
#define MTLDevice_newTextureWithDescriptor(id, desc) object_send(id, "newTextureWithDescriptor:", desc)
#define MTLLibrary_newFunctionWithName(id, name) object_send(id, "newFunctionWithName:", NSString_stringWithUTF8String(name))
#define MTLLibrary_autorelease(id) object_senda(id, "autorelease")
#define MTLFunction_autorelease(id) object_senda(id, "autorelease")
#define MTLRenderPipelineDescriptor_alloc() class_senda("MTLRenderPipelineDescriptor", "alloc")
#define MTLRenderPipelineDescriptor_init(id) object_senda(id, "init")
#define MTLRenderPipelineDescriptor_autorelease(id) object_senda(id, "autorelease")
#define MTLRenderPipelineDescriptor_setFragmentFunction(id, func) object_send(id, "setFragmentFunction:", func)
#define MTLRenderPipelineDescriptor_setVertexFunction(id, func) object_send(id, "setVertexFunction:", func)
#define MTLRenderPipelineDescriptor_colorAttachments(id) object_senda(id, "colorAttachments")
#define MTLRenderPipelineColorAttachmentDescriptorArray_objectAtIndexedSubscript(id, n) object_send(id, "objectAtIndexedSubscript:", n)
#define MTLRenderPipelineColorAttachmentDescriptor_setPixelFormat(id, fmt) object_send(id, "setPixelFormat:", fmt)
#define MTLRenderPipelineState_autorelease(id) object_senda(id, "autorelease")
#define MTLTextureDescriptor_alloc() class_senda("MTLTextureDescriptor", "alloc")
#define MTLTextureDescriptor_init(id) object_senda(id, "init")
#define MTLTextureDescriptor_autorelease(id) object_senda(id, "autorelease")
#define MTLTextureDescriptor_setPixelFormat(id, fmt) object_send(id, "setPixelFormat:", fmt)
#define MTLTextureDescriptor_setWidth(id, width) object_send(id, "setWidth:", width)
#define MTLTextureDescriptor_setHeight(id, height) object_send(id, "setHeight:", height)
#define MTLTexture_autorelease(id) object_senda(id, "autorelease")
#define MTLTexture_replaceRegion(id, region, mipmap, bytes, row) object_send(id, "replaceRegion:mipmapLevel:withBytes:bytesPerRow:", region, mipmap, bytes, row)
#define MTLRenderPassDescriptor_renderPassDescriptor() class_senda("MTLRenderPassDescriptor", "renderPassDescriptor")
#define MTLRenderPassDescriptor_colorAttachments(id) object_senda(id, "colorAttachments")
#define MTLRenderPassDescriptor_autorelease(id) object_senda(id, "autorelease")
#define MTLRenderPassColorAttachmentDescriptorArray_objectAtIndexedSubscript(id, n) object_send(id, "objectAtIndexedSubscript:", n)
#define MTLRenderPassColorAttachmentDescriptor_setTexture(id, tex) object_send(id, "setTexture:", tex)
#define MTLDrawable_texture(id) object_senda(id, "texture")
#define MTLCommandQueue_autorelease(id) object_senda(id, "autorelease")
#define MTLCommandQueue_commandBuffer(id) object_senda(id, "commandBuffer")
#define MTLCommandBuffer_renderCommandEncoderWithDescriptor(id, desc) object_send(id, "renderCommandEncoderWithDescriptor:", desc)
#define MTLCommandBuffer_presentDrawable(id, drawable) object_send(id, "presentDrawable:", drawable)
#define MTLCommandBuffer_commit(id) object_senda(id, "commit")
#define MTLRenderCommandEncoder_setRenderPipelineState(id, state) object_send(id, "setRenderPipelineState:", state)
#define MTLRenderCommandEncoder_setFragmentTexture(id, tex, i) object_send(id, "setFragmentTexture:atIndex:", tex, i)
#define MTLRenderCommandEncoder_drawPrimitives(id, mode, i, n) object_send(id, "drawPrimitives:vertexStart:vertexCount:", mode, i, n)
#define MTLRenderCommandEncoder_endEncoding(id) object_senda(id, "endEncoding")

#define NSApplicationActivationPolicyRegular (0)
#define NSBackingStoreBuffered (2)
#define NSWindowStyleMaskTitled (1 << 0)
#define NSWindowStyleMaskClosable (1 << 1)
#define NSWindowStyleMaskFullSizeContentView (1 << 15)
#define NSEventMaskKeyDown (1 << 10)
#define NSEventMaskAny (NSUIntegerMax)
#define bgra8Unorm (80)
#define triangleStrip (4)

extern id const NSDefaultRunLoopMode;
extern id MTLCreateSystemDefaultDevice();

struct MTLRegion {
	struct { NSUInteger x, y, z; } origin;
	struct { NSUInteger width, height, depth; } size;
};

struct screen {
	int width;
	int height;
	id pool;
	id app;
	id layer;
	id queue;
	id state;
	id texture;
	id pass;
	uint32_t *pixels;
};

struct screen *screen_new(char *title, int width, int height) {
	struct screen *screen = calloc(1, sizeof(struct screen));
	screen->width = width;
	screen->height = height;
	screen->pixels = calloc(screen->width * screen->height, sizeof(uint32_t));

	screen->pool = NSAutoreleasePool_init(NSAutoreleasePool_alloc());
	screen->app = NSApplication_sharedApplication();
	NSApplication_autorelease(screen->app);
	NSApplication_setActivationPolicy(screen->app, NSApplicationActivationPolicyRegular);
	NSApplication_activateIgnoringOtherApps(screen->app, YES);

	CGRect rect = CGRectMake(0, 0, width * 2, height * 2);
	id window = NSWindow_initWithContentRect(NSWindow_alloc(), rect, NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskFullSizeContentView, NSBackingStoreBuffered, NO);
	NSWindow_autorelease(window);
	NSWindow_center(window);
	NSWindow_setTitle(window, title);
	NSWindow_makeKeyAndOrderFront(window);

	id device = MTLCreateSystemDefaultDevice();
	MTLDevice_autorelease(device);

	screen->layer = CAMetalLayer_layer();
	CAMetalLayer_autorelease(screen->layer);
	CAMetalLayer_setDevice(screen->layer, device);
	NSView_setLayer(NSWindow_contentView(window), screen->layer);

	id library = MTLDevice_newLibraryWithSource(device, shader);
	MTLLibrary_autorelease(library);
	id vertex = MTLLibrary_newFunctionWithName(library, "compute");
	MTLFunction_autorelease(vertex);
	id fragment = MTLLibrary_newFunctionWithName(library, "sample");
	MTLFunction_autorelease(fragment);
	id pipeline = MTLRenderPipelineDescriptor_init(MTLRenderPipelineDescriptor_alloc());
	MTLRenderPipelineDescriptor_autorelease(pipeline);
	MTLRenderPipelineDescriptor_setFragmentFunction(pipeline, fragment);
	MTLRenderPipelineDescriptor_setVertexFunction(pipeline, vertex);
	MTLRenderPipelineColorAttachmentDescriptor_setPixelFormat(MTLRenderPipelineColorAttachmentDescriptorArray_objectAtIndexedSubscript(MTLRenderPipelineDescriptor_colorAttachments(pipeline), 0), bgra8Unorm);
	screen->state = MTLDevice_newRenderPipelineStateWithDescriptor(device, pipeline);
	MTLRenderPipelineState_autorelease(screen->state);
	screen->queue = MTLDevice_newCommandQueue(device);
	MTLCommandQueue_autorelease(screen->queue);

	id texture = MTLTextureDescriptor_init(MTLTextureDescriptor_alloc());
	MTLTextureDescriptor_autorelease(texture);
	MTLTextureDescriptor_setPixelFormat(texture, bgra8Unorm);
	MTLTextureDescriptor_setWidth(texture, screen->width);
	MTLTextureDescriptor_setHeight(texture, screen->height);
	screen->texture = MTLDevice_newTextureWithDescriptor(device, texture);
	MTLTexture_autorelease(screen->texture);

	screen->pass = MTLRenderPassDescriptor_renderPassDescriptor();

	return screen;
}

void screen_pixel(struct screen *screen, uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
	screen->pixels[screen->width * y + x] = 0xFF000000 | (b << 16) | (g << 8) | r;
}

void screen_update(struct screen *screen) {
	struct MTLRegion region = { { 0, 0, 0 }, { screen->width, screen->height, 1 } };
	MTLTexture_replaceRegion(screen->texture, region, 0, screen->pixels, 4 * screen->width);

	id drawable = CAMetalLayer_nextDrawable(screen->layer);
	MTLRenderPassColorAttachmentDescriptor_setTexture(MTLRenderPassColorAttachmentDescriptorArray_objectAtIndexedSubscript(MTLRenderPassDescriptor_colorAttachments(screen->pass), 0), MTLDrawable_texture(drawable));

	id buffer = MTLCommandQueue_commandBuffer(screen->queue);
	id encoder = MTLCommandBuffer_renderCommandEncoderWithDescriptor(buffer, screen->pass);
	MTLRenderCommandEncoder_setRenderPipelineState(encoder, screen->state);
	MTLRenderCommandEncoder_setFragmentTexture(encoder, screen->texture, 0);
	MTLRenderCommandEncoder_drawPrimitives(encoder, triangleStrip, 0, 4);
	MTLRenderCommandEncoder_endEncoding(encoder);

	MTLCommandBuffer_presentDrawable(buffer, drawable);
	MTLCommandBuffer_commit(buffer);

	id event = NSApplication_nextEventMatchingMask(screen->app, NSEventMaskAny & ~NSEventMaskKeyDown, NSDate_distantPast(), NSDefaultRunLoopMode, YES);
	if (event) {
		NSApplication_sendEvent(screen->app, event);
		NSApplication_updateWindows(screen->app);
	}
}

void screen_destroy(struct screen *screen) {
	NSAutoreleasePool_drain(screen->pool);
	free(screen->pixels);
	free(screen);
}