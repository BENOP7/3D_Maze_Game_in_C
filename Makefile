all:
	gcc -o game init.c update.c render.c parser.c main.c -lSDL2 -lm