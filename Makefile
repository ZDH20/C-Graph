CC=gcc
CFLAGS=-Werror -Wall -Wextra -std=c99 -pedantic
DEPS=graph.h
OBJ=main.o graph.o

%.o: %.c $(DEPS)
        $(CC) -c -o $@ $< $(CLFAGS)

main: $(OBJ)
        $(CC) -o $@ $^ $(CFLAGS)
