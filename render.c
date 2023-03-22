#include "render.h"

void render(SDL_Renderer * renderer, SDL_Window *window, const int map[9][9])
{
    SDL_SetRenderDrawColor(renderer, 17, 78, 170, 255);

    SDL_RenderDrawLine(renderer,  DISPLAY_OFFSETX,  DISPLAY_OFFSETY,
                       DISPLAY_OFFSETX + PPLANE_WIDTH,  DISPLAY_OFFSETY);
    SDL_RenderDrawLine(renderer,  DISPLAY_OFFSETX + PPLANE_WIDTH,
                       DISPLAY_OFFSETY, DISPLAY_OFFSETX + PPLANE_WIDTH,
                       DISPLAY_OFFSETY + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer,  DISPLAY_OFFSETX,  DISPLAY_OFFSETY, DISPLAY_OFFSETX,  DISPLAY_OFFSETY + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer,  DISPLAY_OFFSETX,  DISPLAY_OFFSETY +
                       PPLANE_HEIGHT, DISPLAY_OFFSETX,  DISPLAY_OFFSETY +
                       PPLANE_HEIGHT);
    
    drawWorld(renderer, map);
    drawPlayer(renderer);

    int x =  posX, y =  posY;
    // if (direction % 30 == 0)
    //     printf("%i\t", direction);
    // SDL_SetRenderDrawColor(renderer,  DISPLAY_OFFSETY, 22, 22, 255);
    // SDL_RenderDrawLine(renderer,  posX,  posY, intersections[0], intersections[1]);


}

void drawWorld(SDL_Renderer *renderer, const int map[9][9])
{
    for (int i = OFFSETX_2D; i <= OFFSETX_2D + PLANE_SIZE2D; i += GRID_SIZE)
    {
        //Draw horizontal grid
        SDL_RenderDrawLine(renderer, OFFSETX_2D, i - 650, OFFSETX_2D +
                           PLANE_SIZE2D, i - 650);
        //Draw vertical grid
        SDL_RenderDrawLine(renderer, i, OFFSETY_2D, i, OFFSETY_2D +
                           PLANE_SIZE2D);
    }

    int idx;
    int idy;
    for (int i = OFFSETX_2D; i < OFFSETX_2D + PLANE_SIZE2D; i += GRID_SIZE)
    {
        idx = (i - OFFSETX_2D) / GRID_SIZE;
        for (int j = OFFSETY_2D; j < OFFSETY_2D + PLANE_SIZE2D; j += GRID_SIZE)
        {
            idy = (j - OFFSETY_2D) / GRID_SIZE;
            if (map[idy][idx] == 1)
            {
                SDL_Rect rect = {i, j, GRID_SIZE, GRID_SIZE};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

}

void drawPlayer(SDL_Renderer *renderer)
{
    int idx, idy;

    SDL_SetRenderDrawColor(renderer, 15, 25, 165, 200);
    SDL_Point points[100];

    for (int i =  posX - 5; i <=  posX + 4; i++)
    {
        idx = i -  posX + 5;

        for (int j =  posY - 5; j <=  posY + 4; j++)
        {
            SDL_Point holder = {i, j};
            points[(int) (10 * idx + j -  posY + 5)] = holder;
        }
        
    }
    // SDL_RenderDrawLine(renderer,  posX,  posY,  posX + pdx * ,  posY + pdy * 8);
    SDL_RenderDrawPoints(renderer, points, 100);
}