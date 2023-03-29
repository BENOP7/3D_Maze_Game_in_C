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

int time_d = 0;
int up_pressed, down_pressed, right_pressed, left_pressed;
int hideMap = 0, q_pressed = 0;
int elapseTime, currentTime, previousTime = 0;
    
int main(int argc, char **argv)
{
    int quit = 0;
    
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

    while (quit == 0)
    {
        currentTime = SDL_GetTicks64();
        elapseTime = currentTime - previousTime;
        previousTime = currentTime;
        SDL_SetRenderDrawColor(renderer, 0x78, 0x78, 0x78, 55);
        SDL_RenderClear(renderer);
        
        quit = handleEvents(&up_pressed, &down_pressed, &left_pressed, &right_pressed, &q_pressed);

        int xo = 0, yo = 0;
        if (pdx < 0) xo = - 30; else xo = 30;
        if (pdy < 0) yo = - 30; else yo = 30;
        int X = (playerX - OFFSETX_2D) / GRID_SIZE, Y = (playerY - OFFSETY_2D) / GRID_SIZE;
        int incX = (playerX - OFFSETX_2D + xo) / GRID_SIZE, decX = (playerX - OFFSETX_2D - xo) / GRID_SIZE;
        int incY = (playerY - OFFSETY_2D+ yo) / GRID_SIZE, decY = (playerY - OFFSETY_2D - yo) / GRID_SIZE;


              
        if (up_pressed && down_pressed)
        {
            pdx = 0;
            pdy = 0;
        }
        else if (up_pressed)
        {
            if (right_pressed)
            {
                direction += elapseTime * 0.2 * UDEG;
                if (direction > P2I)
                        direction -= P2I;
                pdx = elapseTime * 0.2 * cos(direction);
                pdy = elapseTime * 0.2 * sin(direction);
            }
            if (left_pressed)
            {
                direction -= elapseTime * 0.2 * UDEG;
                if (direction < 0)
                        direction += P2I;
                pdx = elapseTime * 0.2 * cos(direction);
                pdy = elapseTime * 0.2 * sin(direction);
            }
            if (worldmap[Y][incX] == 0)
                playerX += pdx;
            if (worldmap[incY][X] == 0)
                playerY += pdy;
        }
        else if (down_pressed)
        {
            if (worldmap[Y][decX] == 0)
                playerX -= pdx;
            if (worldmap[decY][X] == 0)
                playerY -= pdy;
        }
        else if (left_pressed)
        {
            // handle left arrow key pressed
             direction -= elapseTime * 0.2 * UDEG;
            if (direction < 0)
                direction += P2I;
            pdx = elapseTime * 0.2 * cos(direction);
            pdy = elapseTime * 0.2 * sin(direction);
        }
        else if (right_pressed)
        {
            // handle right arrow key pressed
            direction += elapseTime * 0.2 * UDEG;
            if (direction > P2I)
                direction -= P2I;
            pdx = elapseTime * 0.2 * cos(direction);
            pdy = elapseTime * 0.2 * sin(direction);
        }
        else if( q_pressed)
        {
            time_d ++;
            if (time_d > 4)
            {
                time_d = 0;
                if (hideMap)
                    hideMap = 0;
                else
                    hideMap = 1;
                q_pressed = 0;
                
            }
        }

        render(renderer, hideMap);
        render3D(renderer, hideMap);

        SDL_RenderPresent(renderer);

        // SDL_Delay(5);
    }

    SDL_close(renderer, window);   

    return 0;
}

int handleEvents(int *up_pressed, int *down_pressed, int *left_pressed,
                 int *right_pressed, int *q_pressed)
{
    SDL_Event e;
    int quit = 0;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_w:
                *up_pressed = 1;
                break;
            case SDLK_s:
                // handle down arrow key pressed
                *down_pressed = 1;
                break;
            case SDLK_a:
                *left_pressed = 1;
                break;
            case SDLK_d:
                *right_pressed = 1;
                // printf("Rightly setup\n");
                break;
            case SDLK_q:
                *q_pressed = 1;
                break;
            case SDLK_SPACE:
                // handle space key pressed
                break;
                // add cases for other keys as needed qqqq
            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
            case SDLK_w:
                *up_pressed = 0;
                break;
            case SDLK_s:
                // handle down arrow key pressed
                *down_pressed = 0;
                break;
            case SDLK_a:
                *left_pressed = 0;
                break;
            case SDLK_d:
                *right_pressed = 0;
                break;
            case SDLK_q:
                *q_pressed = 0;
                break;
            }
            break;
        default:
            break;
        }
    }

    return (quit);
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
