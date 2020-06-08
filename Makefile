CC = gcc
CFLAGS = -Wall -Werror
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
RM = rm -f

all: clean codageConv

codageConv: codageConv.c
	$(CC) -o codageConv codageConv.c

.PHONY: clean

clean:
	$(RM) $(OBJECTS) codageConv
