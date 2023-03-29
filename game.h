#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#define UNUSED(x) (void) (x)

void gameLoop(SDL_Renderer *renderer);
void handleKeydown(int);
void handleKeyup(int);
void handlePlayerRotationInput(int, int);
void handleQPressed();

void handleInputAction(int);
#endif