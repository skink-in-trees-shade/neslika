CFLAGS  = -Wall -Wextra -Werror -Wpedantic -Wno-unused-result -Wno-newline-eof -std=c99 -Isrc -pipe -g

ifeq ($(OS),Windows_NT)
	PLATFORM = windows
	LDFLAGS = -ld2d1 -lwinmm
else
	SYSTEM = $(shell uname -s)
	ifeq ($(SYSTEM),Darwin)
		PLATFORM = mac
		LDFLAGS = -framework Cocoa -framework Metal -framework AudioUnit
	else ifeq ($(SYSTEM),Linux)
		PLATFORM = linux
		LDFLAGS = -lX11 -lGL -lasound
	endif
endif

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES = $(filter-out src/platform/%.c, $(call rwildcard,src/,*.c)) $(wildcard src/platform/$(PLATFORM)/*.c)
OBJECTS = $(SOURCES:.c=.o)
DEPENDS = $(SOURCES:.c=.d)
TARGET  = neslika

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

-include $(DEPENDS)

clean:
	rm -f $(OBJECTS) $(DEPENDS) $(TARGET)

.PHONY: clean