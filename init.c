#include "init.h"
#include <stdlib.h>
#include <math.h>

int SDL_create(SDL_Window **window, SDL_Renderer **renderer)
{
     *window = SDL_CreateWindow("Maze Shooter", SDL_WINDOWPOS_CENTERED,
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
   
    // for (int i = 0; i < GRID_NUM; i++)
    // {
    //     for (int j = 0; j < GRID_NUM; j++)
    //     {
    //         worldmap[i][j] = 0;
    //     }
    // }
    
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

    playerX = OFFSETX_2D + 144;
    playerY = OFFSETY_2D + 270;
    direction = ANGLE_60;
    pdx = 4 * cos(direction);
    pdy = 4 * sin(direction);

}