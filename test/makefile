CFLAGS = -Wall -Wextra -pedantic --std=c99 -I../lib

SRC = $(wildcard *.c */*.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)
LIB = ../lib/lib6502.a
BIN = test6502

$(BIN): $(OBJ) $(LIB)
	gcc $(CFLAGS) -o $@ $^ $(LIB)

-include $(DEP)

%.o: %.c
	gcc $(CFLAGS) -MMD -c -o $@ $<

clean:
	-rm $(OBJ) $(DEP) $(BIN)

.PHONY: clean