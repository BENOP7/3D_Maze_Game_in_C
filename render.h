#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "game.h"
#include "update.h"

void render(SDL_Renderer *, int);
void drawPlayer(SDL_Renderer *);
void renderMap(SDL_Renderer *);
void render3D(SDL_Renderer *, int);

#endif