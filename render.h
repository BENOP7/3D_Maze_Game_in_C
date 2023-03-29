#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

void render(SDL_Renderer *, int);
void render3D(SDL_Renderer *renderer, int hideMap);
void drawPlayer(SDL_Renderer *);
void drawWorld(SDL_Renderer *);
void drawWeapon(SDL_Renderer *);
void print();

#endif