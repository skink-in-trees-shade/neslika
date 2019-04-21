CFLAGS = -Wall -Wextra -pedantic -I../lib -L../lib
LDFLAGS = -l6502

SRC = $(wildcard *.c */*.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(SRC:%.c=%.d)
BIN = test.exe

$(BIN): $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

-include $(DEP)

%.o: %.c
	gcc $(CFLAGS) -MMD -c -o $@ $<

clean:
	del $(OBJ) $(DEP) $(BIN)

.PHONY: clean