#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "game.h"
#include "init.h"
#include "update.h"
#include "render.h"
#include "parser.h"

const double PI = 3.1415926535897932;
const double PI_HALF = PI / 2;
const double ANGLE_60 = PI / 3;
const double ANGLE_30 = ANGLE_60 / 2;
const double PI_HALF3 = PI_HALF * 3;
const double P2I = PI * 2;

int time_d;
int up_pressed;
int down_pressed;
int right_pressed;
int left_pressed;
int hideMap;
int q_pressed;

#define FOV ANGLE_60
const double INCR = FOV / PPLANE_WIDTH;

// Player's coordinate
float playerX;
float playerY;
float pdx, pdy;
float direction;

//tables
double *cosine;
double *sine;
double *tangent;
double *aTan;

//world
int worldmap[GRID_NUM][GRID_NUM];

    
int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (argc == 2)
    {
            if (parseMap(argv[1]) != 0)
            {
                fprintf(stderr, "Error while parsing map file\n");
                return (EXIT_FAILURE);
            }
    }
    
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return (EXIT_FAILURE);
    }
    init(&window, &renderer);

    gameLoop(renderer);

    SDL_close(renderer, window);   

    return 0;
}


void SDL_close(SDL_Renderer *renderer, SDL_Window *window)
{
    //Destroy renderer
    SDL_DestroyRenderer(renderer);
    // Destroy window
    SDL_DestroyWindow(window);

    free(cosine);
    free(sine);
    free(tangent);
    free(aTan);
    // Quit SDL subsystems
    SDL_Quit();
}
