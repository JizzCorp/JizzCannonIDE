CFLAGS = -lSDL3
CC = gcc

all:
	$(CC) src/main.c -o jizzCannonIDE $(CFLAGS)
