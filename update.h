#ifndef UPDATE_H
#define UPDATE_H

#include "game.h"
#include <math.h>

void checkHorizontalIntersection(const int map[9][9], SDL_Renderer *renderer);
double dist(int ax, int ay, int bx, int by);

#endif