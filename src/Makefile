GENERAL_FLAGS = -Wall -g -c
SDL_FLAGS = -lSDL3
ALL_FLAGS = -Wall -g
CC = gcc

all: main.o button.o
	$(CC) objects/main.o objects/button.o -o build/jizzCannonIDE $(ALL_FLAGS) $(SDL_FLAGS)

.PHONY: main.o
main.o: main.c
	$(CC) main.c -o objects/main.o $(GENERAL_FLAGS) $(SDL_FLAGS)

.PHONY: button.o
button.o: widgets/button.c
	$(CC) widgets/button.c -o objects/button.o $(GENERAL_FLAGS) $(SDL_FLAGS)
