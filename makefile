CFLAGS  = -Wall -Wextra -Werror -Wpedantic -Wno-unused-result -std=c99 -Isrc -pipe `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES = $(call rwildcard,src/,*.c)
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