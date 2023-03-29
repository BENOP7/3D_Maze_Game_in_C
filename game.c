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
        SDL_SetRenderDrawColor(renderer, 0x78, 0x78, 0x78, 55);
        SDL_RenderClear(renderer);

        currentTime = SDL_GetTicks64();
        elapseTime = currentTime - previousTime;
        previousTime = currentTime;

        quit = handleEvents();

        handleInputAction(elapseTime);

        render(renderer, hideMap);
        render3D(renderer, hideMap);

        SDL_RenderPresent(renderer);

        /* SDL_Delay(5); */
    }
}

