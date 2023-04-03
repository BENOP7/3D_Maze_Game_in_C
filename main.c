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

sprite_t sprites[10]; /* list of all sprites */

    
int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    if (parseMap(argv[1]) != 0)
    {
        fprintf(stderr, "Error while parsing map file\n");
        return (EXIT_FAILURE);
    }
    init(&window, &renderer);

    gameLoop(renderer);

    SDL_close(renderer, window);

    return 0;
}

void init(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (SDL_create(window, renderer) != 0)
    {
        fprintf(stderr, "Could not initialize SDL window! SDL_Error: %s\n",
                SDL_GetError());
        exit(EXIT_FAILURE);
    }

    initTables();

    time_d = 0;
    up_pressed = 0, down_pressed = 0, right_pressed = 0, left_pressed = 0;
    hideMap = 0, q_pressed = 0;
    sprites[0].type = 1, sprites[0].shown = 1, sprites[0].map = 0, sprites[0].x = sprites[0].y = 268,
    sprites[0].z = 20;
    
    playerX = OFFSETX_2D + 300;
    playerY = OFFSETY_2D + 280;
    direction = ANGLE_60;
    pdx = 4 * cos(direction);
    pdy = 4 * sin(direction);

}

int SDL_create(SDL_Window **window, SDL_Renderer **renderer)
{
    *window = SDL_CreateWindow("Maze Shooter - 3D Game",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n",
                SDL_GetError());
        return (EXIT_FAILURE);
    }
    *renderer = SDL_CreateRenderer(*window, -1,
                                                SDL_RENDERER_ACCELERATED
                                                | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL)
    {
        fprintf(stderr, "SDL Renderer could not be created! SDL_Error: %s\n",
                SDL_GetError());
        return (EXIT_FAILURE);
    }

    return (0);
}

void initTables()
{
    cosine = malloc(sizeof(*cosine) * 360);
    sine = malloc(sizeof(*sine) * 360);
    tangent = malloc(sizeof(*tangent) * 360);
    aTan = malloc(sizeof(*aTan) * 360);
    if (cosine == NULL || sine == NULL || tangent == NULL || aTan == NULL)
    {
        printf("Memory alloc error!");
        free(cosine);
        free(sine);
        free(tangent);
        free(aTan);
        exit(EXIT_FAILURE);
    }
    for (int n = 0; n < 360; n++)
    {
        cosine[n] = cos(UDEG * n);    
        sine[n] = sin(UDEG * n);
        tangent[n] = tan(UDEG * n);
        aTan[n] = 1 / tangent[n];
    }
    printf("Here I go!\n");
}

void SDL_close(SDL_Renderer *renderer, SDL_Window *window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    free(cosine);
    free(sine);
    free(tangent);
    free(aTan);

    SDL_Quit();
}
