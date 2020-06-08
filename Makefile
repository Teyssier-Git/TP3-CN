CC = gcc
CFLAGS = -Wall -Werror
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
RM = rm -f

all: clean codageConv decodageConv decodageEuclidien

codageConv: codageConv.c
	$(CC) -o codageConv codageConv.c

decodageConv: decodageConv.c
	$(CC) -o decodageConv decodageConv.c

decodageEuclidien: decodageEuclidien.c
	$(CC) -o decodageEuclidien decodageEuclidien.c

.PHONY: clean test

clean:
	$(RM) $(OBJECTS) codageConv decodageConv decodageEuclidien

test:
	./codageConv 00101110
	./decodageConv 0000111000011001
	./decodageConv 0100111000011001
	./decodageConv 0010101000011001
	./decodageConv 0001011000111001
