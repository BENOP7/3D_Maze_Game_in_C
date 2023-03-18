#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "render.h"

const double PI = 3.1415926535;
const double P2I = 2 * PI;
const double PI_HALF = (PI / 2);
const double PI_HALF3 = (3 * PI_HALF);
const double ANGLE_60 = PI / 3;
const double ANGLE_45 = PI_HALF / 2;
const double ANGLE_30 = ANGLE_60 / 2;
#define FOV ANGLE_60
const double INCR = FOV / PPLANE_WIDTH;

double posX = 45;
double posY = 64;
double pdx = 0;
double pdy = 0;
double direction = 0.0;

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    
    if (init_window(&window, &renderer) != 0)
        return (EXIT_FAILURE);
    
    gameloop(window, renderer);

    //Destroy Renderer and Window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return (0);
}

/**
 * init_window - Initializes the sdl library and creates a window and renderer
 * 
 * window: SDL window
 * renderer: SDL renderer
 * 
*/
int init_window(SDL_Window **window, SDL_Renderer **renderer)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }
    // Create window
    *window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (*window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (*renderer == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return (EXIT_FAILURE);
    }

    return (0);
}

/**
 * gameloop - This is function handles updates for each frame and
 * possible events
 * 
 * window: The SDL window
 * renderer: The SDL renderer
 * 
*/
void gameloop(SDL_Window *window, SDL_Renderer *renderer)
{
    int up_pressed = 0, down_pressed = 0, left_pressed = 0, right_pressed = 0; 
    SDL_Event e;
    int quit = 0;
    while (quit == 0)
    {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 255);
        SDL_RenderClear(renderer);
        
        while (SDL_PollEvent(&e))
        {
            eventHandler(e, &quit, &up_pressed, &down_pressed, &left_pressed, &right_pressed);
        }
        render(renderer, window, NULL);

        SDL_RenderPresent(renderer);

    }
}

/**
 * eventHandler - Handle window and keyboard events such as keypressed
 * and close window button clicked
 * 
 * e: SDL event
 * quit: flag to close the window
 * up_pressed: key up has been pressed? (boolean)
 * down_pressed: key down has been pressed? (boolean)
 * left_pressed: key left has been pressed? (boolean)
 * right_pressed: key right has been pressed? (boolean)
 * 
*/
void eventHandler(SDL_Event e, int *quit, int *up_pressed, int *down_pressed, int *left_pressed, int *right_pressed)
{
    switch (e.type)
    {
    case SDL_QUIT:
        *quit = 1;
        break;
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            *up_pressed = 1;
            break;
        case SDLK_DOWN:
            // handle down arrow key pressed
            *down_pressed = 1;
            break;
        case SDLK_LEFT:
            *left_pressed = 1;
            break;
        case SDLK_RIGHT:
            *right_pressed = 1;
            break;
        case SDLK_SPACE:
            // handle space key pressed
            break;
            // add cases for other keys as needed
        }
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            *up_pressed = 0;
            break;
        case SDLK_DOWN:
            // handle down arrow key pressed
            *down_pressed = 0;
            break;
        case SDLK_LEFT:
            *left_pressed = 0;
            break;
        case SDLK_RIGHT:
            *right_pressed = 0;
            break;
        }
        break;
    default:
        break;
    }
}