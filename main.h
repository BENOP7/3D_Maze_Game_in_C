#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>

// Screen dimension constants
#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 720
#define GRID_SIZE 64
#define PLANE_SIZE2D (GRID_SIZE * 9)
#define PPLANE_WIDTH 640
#define PPLANE_HEIGHT 480
#define DD 277

#define OFFSETX_2D 700
#define OFFSETY_2D 50
#define UDEG 0.0174533


extern const double PI;
extern const double P2I;
extern const double PI_HALF;
extern const double PI_HALF3;
extern const double ANGLE_60;
extern const double ANGLE_45;
extern const double ANGLE_30;
// #define FOV ANGLE_60
extern const double INCR;

// Player's coordinate
extern double posX;
extern double posY;
extern double pdx, pdy;
extern double direction;


int init_window(SDL_Window **, SDL_Renderer **);
void gameloop(SDL_Window *, SDL_Renderer *);
void eventHandler(SDL_Event e, int *quit, int *up_pressed, int *down_pressed, int *left_pressed, int *right_pressed);

#endif