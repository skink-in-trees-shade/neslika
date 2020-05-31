CFLAGS  = -Wall -Wextra -Werror -Wpedantic -std=c11 -Isrc
LDFLAGS =

SOURCES = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)
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