TARGET= project
CFLAGS=-g -W -Wall -Wextra -MMD
LDFLAGS=-LGraphique
LDLIBS=-lgraph -lSDL -lSDL_ttf
SRC=$(wildcard *.c)
DEPS=$(SRC:.c=.d)
OBJ=$(SRC:.c=.o)

default: $(TARGET)

.c.o:
	gcc $(CFLAGS) -c $<

$(TARGET): $(OBJ)
	gcc $(LDFLAGS) $^ $(LDLIBS)  -o $@

-include $(DEPS)


.PHONY: clean

clean:
	rm -f *.o
	rm -f *.d
	rm -f $(TARGET)


.PHONY: clangtidy

clangtidy:
	clang-tidy --checks="readability-*" *.c *.h
