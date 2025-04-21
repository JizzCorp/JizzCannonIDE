GENERAL_FLAGS = -Wall -g -c -fsanitize=address
SDL_FLAGS = -lSDL3
ALL_FLAGS = -Wall -g -fsanitize=address
CC = gcc

all: dynList.o button.o app.o main.o 
	$(CC) objects/main.o objects/app.o objects/dynList.o objects/button.o -o build/jizzCannonIDE $(ALL_FLAGS) $(SDL_FLAGS)

.PHONY: main.o
main.o: main.c
	$(CC) main.c -o objects/main.o $(GENERAL_FLAGS) $(SDL_FLAGS)

.PHONY: app.o
app.o:
	$(CC) JizzCannon/app.c -o objects/app.o $(GENERAL_FLAGS)

.PHONY: button.o
button.o: JizzCannon/widgets/button.c
	$(CC) JizzCannon/widgets/button.c -o objects/button.o $(GENERAL_FLAGS) $(SDL_FLAGS)

.PHONY: dynList.o
dynList.o: JizzCannon/utils/DynList/dynList.c
	$(CC) JizzCannon/utils/DynList/dynList.c -o objects/dynList.o $(GENERAL_FLAGS)

