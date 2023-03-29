#include "main.h"
#include "game.h"

void handleInputAction(int elapse)
{
    int xo = 0, yo = 0;
    if (pdx < 0)
        xo = - 30;
    else
        xo = 30;
    if (pdy < 0)
        yo = - 30;
    else
        yo = 30;
    int X = (playerX - OFFSETX_2D) / GRID_SIZE;
    int Y = (playerY - OFFSETY_2D) / GRID_SIZE;
    int incX = (playerX - OFFSETX_2D + xo) / GRID_SIZE;
    int decX = (playerX - OFFSETX_2D - xo) / GRID_SIZE;
    int incY = (playerY - OFFSETY_2D + yo) / GRID_SIZE;
    int decY = (playerY - OFFSETY_2D - yo) / GRID_SIZE;

    if (up_pressed && down_pressed)
        pdx = 0, pdy = 0;
    else if (up_pressed)
    {
        if (right_pressed)
            handlePlayerRotationInput(1, elapse);
        if (left_pressed)
            handlePlayerRotationInput(0, elapse);
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
        handlePlayerRotationInput(0, elapse);
    else if (right_pressed)
        handlePlayerRotationInput(1, elapse);
    else if (q_pressed)
        handleQPressed();
}

void handlePlayerRotationInput(int right, int elapse)
{
    if (!right)
    {
        direction -= elapse * 0.2 * UDEG;
        if (direction < 0)
            direction += P2I;
        pdx = elapse * 0.2 * cos(direction);
        pdy = elapse * 0.2 * sin(direction);
    }
    else
    {
        direction += elapse * 0.2 * UDEG;
        if (direction > P2I)
            direction -= P2I;
        pdx = elapse * 0.2 * cos(direction);
        pdy = elapse * 0.2 * sin(direction);
    }
    
}

void handleQPressed()
{
    time_d++;
    if (time_d > 3)
    {
        time_d = 0;
        if (hideMap)
            hideMap = 0;
        else
            hideMap = 1;
        q_pressed = 0;
    }
}

void handleKeydown(int type)
{
    switch (type)
    {
    case SDLK_w:
        up_pressed = 1;
        break;
    case SDLK_s:
        // handle down arrow key pressed
        down_pressed = 1;
        break;
    case SDLK_a:
        left_pressed = 1;
        break;
    case SDLK_d:
        right_pressed = 1;
        // printf("Rightly setup\n");
        break;
    case SDLK_q:
        q_pressed = 1;
        break;
    case SDLK_SPACE:
        // handle space key pressed
        break;
        // add cases for other keys as needed qqqq
    }
}

void handleKeyup(int type)
{
    switch (type)
    {
    case SDLK_w:
        up_pressed = 0;
        break;
    case SDLK_s:
        // handle down arrow key pressed
        down_pressed = 0;
        break;
    case SDLK_a:
        left_pressed = 0;
        break;
    case SDLK_d:
        right_pressed = 0;
        // printf("Rightly setup\n");
        break;
    case SDLK_q:
        q_pressed = 0;
        break;
    case SDLK_SPACE:
        // handle space key pressed
        break;
        // add cases for other keys as needed qqqq
    }
}

int handleEvents()
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
            handleKeydown(e.key.keysym.sym);
            break;
        case SDL_KEYUP:
            handleKeyup(e.key.keysym.sym);
            break;
        default:
            break;
        }
    }

    return (quit);
}
