#include "render.h"



void render(SDL_Renderer * renderer, SDL_Window *window, const int map[9][9])
{
    direction = P2I;
    
    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 170);

    SDL_RenderDrawLine(renderer, 110, 160, 110 + PPLANE_WIDTH, 160);
    SDL_RenderDrawLine(renderer, 110 + PPLANE_WIDTH, 160, 110 + PPLANE_WIDTH, 360);
    SDL_RenderDrawLine(renderer, 110, 160 + PPLANE_HEIGHT, 110, 160 + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer, 110 + PPLANE_WIDTH, 160, 110 + PPLANE_WIDTH, 160 + PPLANE_HEIGHT);
    for (int i = OFFSETX_2D; i <= OFFSETX_2D + PLANE_SIZE2D; i += GRID_SIZE)
    {
        //Draw horizontal grid
        SDL_RenderDrawLine(renderer, OFFSETX_2D, i - 650, OFFSETX_2D + PLANE_SIZE2D, i - 650);
        //Draw vertical grid
        SDL_RenderDrawLine(renderer, i, OFFSETY_2D, i, OFFSETY_2D + PLANE_SIZE2D);
    }

    int idx;
    int idy;
    // for (int i = OFFSETX_2D; i < OFFSETX_2D + PLANE_SIZE2D; i += GRID_SIZE)
    // {
    //     idx = (i - OFFSETX_2D) / GRID_SIZE;
    //     for (int j = OFFSETY_2D; j < OFFSETY_2D + PLANE_SIZE2D; j += GRID_SIZE)
    //     {
    //         idy = (j - OFFSETY_2D) / GRID_SIZE;
    //         if (map[idy][idx] == 1)
    //         {
    //             SDL_Rect rect = {i, j, GRID_SIZE, GRID_SIZE};
    //             SDL_RenderFillRect(renderer, &rect);
    //         }
    //         // else{
                
    //         // }
    //     }
    // }

    SDL_SetRenderDrawColor(renderer, 15, 25, 165, 200);
    SDL_Point points[100];

    for (int i = posX - 5; i <= posX + 4; i++)
    {
        idx = i - posX + 5;

        for (int j = posY - 5; j <= posY + 4; j++)
        {
            SDL_Point holder = {.x = i, .y = j};
            points[(int) (10 * idx + j - posY + 5)] = holder;
        }
        
    }
    SDL_RenderDrawLine(renderer, posX, posY, posX + pdx * 3, posY + pdy * 3);
    SDL_RenderDrawPoints(renderer, points, 100);

    // if (direction % 30 == 0)
    //     printf("%i\t", direction);
    // SDL_SetRenderDrawColor(renderer, 160, 22, 22, 255);
    // SDL_RenderDrawLine(renderer, playerX, playerY, intersections[0], intersections[1]);


}