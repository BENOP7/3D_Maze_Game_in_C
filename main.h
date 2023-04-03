#ifndef _MAIN_H_
#define _MAIN_H_

#include <SDL2/SDL.h>

// Screen dimension extern constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 544
#define GRID_SIZE 64
#define GRID_NUM 20
#define PLANE_SIZE2D (GRID_SIZE * GRID_NUM)
#define PPLANE_WIDTH 640
#define PPLANE_HEIGHT 480                     
#define DD 300                                /* Distance from player to projection plane*/

#define OFFSETX_2D 55
#define OFFSETY_2D 374
#define UDEG 0.017453292519943
#define DISPLAY_OFFSETX 0
#define DISPLAY_OFFSETY 0

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
extern float playerMapX;
extern float playerMapY;

extern int worldmap[GRID_NUM][GRID_NUM];

extern double *cosine;
extern double *sine;
extern double *tangent;
extern double *aTan;

extern int time_d;
extern int up_pressed;
extern int down_pressed;
extern int right_pressed;
extern int left_pressed;
extern int hideMap;
extern int q_pressed;

typedef struct sprite
{
    int type;
    int shown;
    int map;
    int x, y, z;
} sprite_t;

extern sprite_t sprites[10];

int handleEvents();
void SDL_close(SDL_Renderer *, SDL_Window *);
void checkEvent(SDL_Event e, int *quit, int *up_pressed, int *down_pressed, int *left_pressed, int *right_pressed);
void eventHandler(int, int, int, int);

#endif