#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

// Screen dimension extern constants
#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 720
#define GRID_SIZE 64
#define GRID_NUM 10
#define PLANE_SIZE2D (GRID_SIZE * GRID_NUM)
#define PPLANE_WIDTH 640
#define PPLANE_HEIGHT 480                     
#define DD 300                                /* Distance from player to projection plane*/

#define OFFSETX_2D 700
#define OFFSETY_2D 50
#define DISPLAY_OFFSETX 45
#define DISPLAY_OFFSETY 95
#define UDEG 0.017453292519943


extern const double ANGLE_60;
extern const double ANGLE_30;
extern  const double PI_HALF;
extern  const double PI_HALF3;
extern const double PI;
extern const double P2I;
extern const double INCR;

extern float playerX;
extern float playerY;
extern float pdx, pdy;
extern float direction;

extern int worldmap[GRID_NUM][GRID_NUM];

int handleEvents(int *, int *, int *, int *, int *);
void SDL_close(SDL_Renderer *, SDL_Window *, double *,
                 double *, double *, double *);
int init_window(SDL_Window **, SDL_Renderer **);
void gameloop(SDL_Renderer *);
void eventHandler(int, int, int, int, int);


#endif