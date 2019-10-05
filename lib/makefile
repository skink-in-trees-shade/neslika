CFLAGS = -Wall -Wextra -pedantic --std=c99 -I. -g

SRC = $(wildcard *.c */*.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)
BIN = lib6502.a

$(BIN): $(OBJ)
	ar rcs $@ $^

-include $(DEP)

%.o: %.c
	gcc $(CFLAGS) -MMD -c -o $@ $<

clean:
	rm $(subst /,\,$(OBJ)) $(subst /,\,$(DEP)) $(subst /,\,$(BIN))

.PHONY: clean