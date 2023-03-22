#ifndef RENDER_H
#define RENDER_H

#include "main.h"

void render(SDL_Renderer *, SDL_Window *, const int map[9][9]);
void drawPlayer(SDL_Renderer *);
void drawWorld(SDL_Renderer *, const int (*)[9]);

#endif