all:
	gcc -o game render.c update.c game.c -lSDL2 -lm