all:
	gcc -Wall -Werror -Wextra -pedantic -o game render.c event.c game.c update.c parser.c init.c main.c -lSDL2 -lm