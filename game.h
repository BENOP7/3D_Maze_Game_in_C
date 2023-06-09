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
#define UDEG 0.017453292519943


extern const double ANGLE_60;
extern const double ANGLE_30;
extern  const double PI_HALF;
extern  const double PI_HALF3;
extern const double PI;
extern const double P2I;
extern const double INCR;

const double PI = 3.1415926535897932;
const double PI_HALF = PI / 2;
const double ANGLE_60 = PI / 3;
const double ANGLE_30 = ANGLE_60 / 2;
const double PI_HALF3 = PI_HALF * 3;
const double P2I = PI * 2;

#define FOV ANGLE_60
const double INCR = FOV / PPLANE_WIDTH;

#endif