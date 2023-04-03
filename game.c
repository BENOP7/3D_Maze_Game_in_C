#include "game.h"
#include "main.h"
#include "render.h"
#include "update.h"

void gameLoop(SDL_Renderer *renderer)
{
    int quit = 0;
    int elapseTime, currentTime, previousTime = 0;

    while (quit == 0)
    {
        SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0);
        SDL_RenderClear(renderer);

        currentTime = SDL_GetTicks64();
        elapseTime = currentTime - previousTime;
        previousTime = currentTime;

        quit = handleEvents();

        handleInputAction(elapseTime);

        
        render3D(renderer, hideMap);
        render(renderer, hideMap);

        SDL_RenderPresent(renderer);
        // printf("FPS: %d  ", 1000 / elapseTime);
        /* SDL_Delay(5); */
    }
}

