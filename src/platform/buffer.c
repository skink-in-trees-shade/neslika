#include <stdlib.h>
#include <string.h>
#include "buffer.h"

struct buffer {
	float *data;
	size_t size;
	size_t read_ptr;
	size_t write_ptr;
	size_t write_avail;
};

struct buffer *buffer_new(size_t size) {
	struct buffer *buffer = calloc(1, sizeof(struct buffer));
	buffer->size = size;
	buffer->write_avail = size;
	buffer->data = calloc(buffer->size, sizeof(float));
	return buffer;
}

size_t buffer_read(struct buffer *buffer, float *data, size_t count) {
	if (!data || count == 0 || buffer->write_avail == buffer->size) {
		return 0;
	}

	size_t read_avail = buffer->size - buffer->write_avail;
	if (count > read_avail) {
		count = read_avail;
	}

	if (count > buffer->size - buffer->read_ptr) {
		size_t len = buffer->size - buffer->read_ptr;
		memcpy(data, &buffer->data[buffer->read_ptr], len * sizeof(float));
		memcpy(&data[len], buffer->data, (count - len) * sizeof(float));
	} else {
		memcpy(data, &buffer->data[buffer->read_ptr], count * sizeof(float));
	}

	buffer->read_ptr = (buffer->read_ptr + count) % buffer->size;
	buffer->write_avail += count;

	return count;
}

size_t buffer_write(struct buffer *buffer, float *data, size_t count) {
	if (!data || count == 0 || buffer->write_avail == 0) {
		return 0;
	}

	if (count > buffer->write_avail) {
		count = buffer->write_avail;
	}

	if (count > buffer->size - buffer->write_ptr) {
		size_t len = buffer->size - buffer->write_ptr;
		memcpy(&buffer->data[buffer->write_ptr], data, len * sizeof(float));
		memcpy(buffer->data, &data[len], (count - len) * sizeof(float));
	} else {
		memcpy(&buffer->data[buffer->write_ptr], data, count * sizeof(float));
	}

	buffer->write_ptr = (buffer->write_ptr + count) % buffer->size;
	buffer->write_avail -= count;

	return count;
}

size_t buffer_available(struct buffer *buffer) {
	return buffer->size - buffer->write_avail;
}

void buffer_destroy(struct buffer *buffer) {
	free(buffer->data);
	free(buffer);
}