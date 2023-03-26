all:
	gcc -o game render.c update.c main.c -lSDL2 -lm