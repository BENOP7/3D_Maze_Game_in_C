all:
	gcc -o game -Isrc/headers -Isrc/include -Lsrc/lib main.c -lmingw32 -lSDL2main -lSDL2 -lm