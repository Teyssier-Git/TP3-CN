CC = gcc
CFLAGS = -Wall -Werror
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
RM = rm -f

all: clean codageConv decodageConv

codageConv: codageConv.c
	$(CC) -o codageConv codageConv.c

decodageConv: decodageConv.c
	$(CC) -o decodageConv decodageConv.c

.PHONY: clean

clean:
	$(RM) $(OBJECTS) codageConv decodageConv
