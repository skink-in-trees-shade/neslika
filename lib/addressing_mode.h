#ifndef ADDRESSING_MODE_H
#define ADDRESSING_MODE_H

typedef enum {
	addressing_implicit,
	addressing_accumulator,
	addressing_immediate,
	addressing_zero_page,
	addressing_zero_page_x,
	addressing_zero_page_y,
	addressing_relative,
	addressing_absolute,
	addressing_absolute_x,
	addressing_absolute_y,
	addressing_indirect,
	addressing_indexed_indirect,
	addressing_indirect_indexed
} addressing_mode_t;

#endif