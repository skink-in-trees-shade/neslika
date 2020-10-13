#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

struct buffer;

struct buffer *buffer_new(size_t size);
size_t buffer_read(struct buffer *buffer, float *data, size_t count);
size_t buffer_write(struct buffer *buffer, float *data, size_t count);
size_t buffer_available(struct buffer *buffer);
void buffer_destroy(struct buffer *buffer);

#endif