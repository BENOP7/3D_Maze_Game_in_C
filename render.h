#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
// #ifndef GAME_H
// #define GAME_H

// #include "game.h"

// #endif

void render(SDL_Renderer *, int);
void render3D(SDL_Renderer *renderer, int hideMap);
void drawPlayer(SDL_Renderer *);
void drawWorld(SDL_Renderer *, const int (*)[9]);

#endif