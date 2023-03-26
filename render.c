#include "game.h"
#include "render.h"

void render(SDL_Renderer * renderer, int hideMap)
{
    
    SDL_SetRenderDrawColor(renderer, 80,32, 16, 255);

    SDL_RenderDrawLine(renderer, 50, 60, 50 + PPLANE_WIDTH, 60);
    SDL_RenderDrawLine(renderer, 50 + PPLANE_WIDTH, 60, 50 + PPLANE_WIDTH, 60 + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer, 50, 60, 50, 60 + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer, 50, 60 + PPLANE_HEIGHT, 50 + PPLANE_WIDTH, 60 + PPLANE_HEIGHT);

    int idx;
    int idy;
    if (!hideMap)
    {
        for (int i = OFFSETX_2D; i <= OFFSETX_2D + PLANE_SIZE2D; i += GRID_SIZE)
        {
            // Draw horizontal grid
            SDL_RenderDrawLine(renderer, OFFSETX_2D, i - 650, OFFSETX_2D + PLANE_SIZE2D, i - 650);
            // Draw vertical grid
            SDL_RenderDrawLine(renderer, i, OFFSETY_2D, i, OFFSETY_2D + PLANE_SIZE2D);
        }

        for (int i = OFFSETX_2D; i < OFFSETX_2D + PLANE_SIZE2D; i += GRID_SIZE)
        {
            idx = (i - OFFSETX_2D) / GRID_SIZE;
            for (int j = OFFSETY_2D; j < OFFSETY_2D + PLANE_SIZE2D; j += GRID_SIZE)
            {
                idy = (j - OFFSETY_2D) / GRID_SIZE;
                if (worldmap[idy][idx] == 1)
                {
                    SDL_Rect rect = {i, j, GRID_SIZE, GRID_SIZE};
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }

        // Draw player
        SDL_SetRenderDrawColor(renderer, 15, 25, 165, 200);
        SDL_Point points[100];

        for (int i = playerX - 5; i <= playerX + 4; i++)
        {
            idx = i - playerX + 5;

            for (int j = playerY - 5; j <= playerY + 4; j++)
            {
                SDL_Point holder = {.x = i, .y = j};
                points[(int)(10 * idx + j - playerY + 5)] = holder;
            }
        }
        SDL_RenderDrawLine(renderer, playerX, playerY, playerX + pdx * 3, playerY + pdy * 3);
        SDL_RenderDrawPoints(renderer, points, 100);
    }
    // if (direction % 30 == 0)
    //     printf("%i\t", direction);
    SDL_SetRenderDrawColor(renderer, 160, 22, 22, 255);
    // SDL_RenderDrawLine(renderer, playerX, playerY, intersections[0], intersections[1]);


}