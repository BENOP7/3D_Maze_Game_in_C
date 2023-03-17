all:
	gcc -Isrc/include -Isrc/headers -L src/lib -o main main.c -lmingw32 -lSDL2main -lSDL2