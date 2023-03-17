#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"


// Player's coordinate
float playerX;
float playerY;
float pdx, pdy;
float direction;

float dist(int ax, int ay, int bx, int by, float angle)
{
    return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) );
}

void checkHorizontalIntersection(const int map[9][9], SDL_Renderer *renderer)
{
    int xo, yo, dof, r, distT, lineH;
    float ray_x, ray_y, ray_direction = direction - ANGLE_30;
    if (ray_direction < 0) ray_direction += P2I; if (ray_direction > P2I) ray_direction -= P2I;
    int coY;
    int coX;

    for (r = 0; r < PPLANE_WIDTH; r++)
    {
        // horizontal
        float distH = 1000000;
        float hx = playerX - OFFSETX_2D, hy = playerY - OFFSETY_2D;
        dof = 0;
        float aTan = - 1 / tan(ray_direction);
        if ( ray_direction > PI)
        {
            ray_y = (((int)(playerY - OFFSETY_2D) >> 6) << 6) - 0.001;
            ray_x = (playerX - OFFSETX_2D) + ((playerY - OFFSETY_2D) - ray_y) * aTan;
            yo = - GRID_SIZE;
            xo = -yo * aTan;
        }
        //vertically
        if ( ray_direction < PI)
        {
            ray_y = (((int)(playerY - OFFSETY_2D) >> 6) << 6) + GRID_SIZE;
            ray_x = (playerX - OFFSETX_2D) + ((playerY - OFFSETY_2D) - ray_y) * aTan;
            yo = GRID_SIZE;
            xo = -yo * aTan;
        }
    
        //looking left or right
        if (ray_direction == P2I || ray_direction == P2I)
        {
            ray_x = playerX - OFFSETX_2D;
            ray_y = playerY - OFFSETY_2D;
            dof = 8;
        }
        while (dof < 8)
        {
            coX = (int) ray_x >> 6;
            coY = (int) ray_y >> 6;
            if (coX >= 0 && coY >= 0 && coX < 9 && coY < 9 && map[coY][coX] > 0)
            {
                hx = ray_x;
                hy = ray_y;
                distH = dist(playerX - OFFSETX_2D, playerY - OFFSETY_2D, hx, hy, ray_direction);
                dof = 8;
            }
            else
            {
                ray_x += xo;
                ray_y += yo;
                dof++;
            }
        }

        // vertical
        float distV = 1000000;
        float vx = playerX - OFFSETX_2D, vy = playerY - OFFSETY_2D;
        dof = 0;
        float nTan = -tan(ray_direction);
        if (ray_direction > PI_HALF && ray_direction < PI_HALF3)
        {
            ray_x = (((int) (playerX - 700) >> 6) << 6) - 0.001;
            ray_y = (playerY - OFFSETY_2D) + ((playerX - OFFSETX_2D) - ray_x) * nTan;
            xo = -GRID_SIZE;
            yo = -xo * nTan;
        }
        // vertically
        if (ray_direction > PI_HALF3 || ray_direction < PI_HALF)
        {
            ray_x = (int) (((int)(playerX - OFFSETX_2D) >> 6) << 6) + GRID_SIZE;
            ray_y = (playerY - OFFSETY_2D) + ((playerX - OFFSETX_2D) - ray_x) * nTan;
            xo = GRID_SIZE;
            yo = -xo * nTan;
        }

        // looking down or up
        if (ray_direction == PI_HALF || ray_direction == PI_HALF3)
        {
            ray_x = playerX - OFFSETX_2D;
            ray_y = playerY - OFFSETY_2D;
            dof = 8;
        }
        while (dof < 8)
        {
            coX = (int) ray_x >> 6;
            coY = (int) ray_y >> 6;
            if (coX >= 0 && coY >= 0 && coX < 9 && coY < 9 && map[coY][coX] > 0)
            {
                vx = ray_x;
                vy = ray_y;
                distV = dist(playerX - OFFSETX_2D, playerY - OFFSETY_2D, vx, vy, ray_direction);
                dof = 8;
            }
            else
            {
                ray_x += xo;
                ray_y += yo;
                dof++;
            }
        }

        if (distV < distH)
        {
            distT = distV;
            ray_x = vx, ray_y = vy;
        }
        if (distH < distV)
        {
            distT = distH;
            ray_x = hx, ray_y = hy;
        }
        lineH = (DD * GRID_SIZE) / distT;
        if (lineH > PPLANE_HEIGHT) lineH = PPLANE_HEIGHT;

        SDL_SetRenderDrawColor(renderer, 45, 100, 154, 250);
        SDL_RenderDrawLine(renderer, 110 + r, 160 + (PPLANE_HEIGHT / 2) - (lineH / 2), r + 110, 160 + (PPLANE_HEIGHT / 2) + (lineH / 2));
        SDL_SetRenderDrawColor(renderer, 255, 222, 0, 255);
        SDL_RenderDrawLine(renderer, playerX, playerY, ray_x + OFFSETX_2D, ray_y + OFFSETY_2D);

        ray_direction += INCR;
        if (ray_direction < 0) ray_direction += P2I; if (ray_direction > P2I) ray_direction -= P2I;
    }
}

int checkVerticalIntersection()
{

}

void render(SDL_Renderer * renderer, SDL_Window *window, const int map[9][9])
{
    
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
            // else{
                
            // }
        }
    }

    SDL_SetRenderDrawColor(renderer, 15, 25, 165, 200);
    SDL_Point points[100];

    for (int i = playerX - 5; i <= playerX + 4; i++)
    {
        idx = i - playerX + 5;

        for (int j = playerY - 5; j <= playerY + 4; j++)
        {
            SDL_Point holder = {.x = i, .y = j};
            points[(int) (10 * idx + j - playerY + 5)] = holder;
        }
        
    }
    SDL_RenderDrawLine(renderer, playerX, playerY, playerX + pdx * 3, playerY + pdy * 3);
    SDL_RenderDrawPoints(renderer, points, 100);

    int x = playerX, y = playerY;
    // if (direction % 30 == 0)
    //     printf("%i\t", direction);
    SDL_SetRenderDrawColor(renderer, 160, 22, 22, 255);
    // SDL_RenderDrawLine(renderer, playerX, playerY, intersections[0], intersections[1]);


}


int main(int argc, char **argv)
{
    // The window we'll be rendering to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    int map[9][9] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 1, 0, 0, 1, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 1, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    //Default player position
    playerX = OFFSETX_2D + 96;
    playerY = OFFSETY_2D + 225;

    direction = 0.0f;                   /* Default player direction */
    pdx = 4 * cos(direction);
    pdy = 4 * sin(direction);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int up_pressed = 0, down_pressed = 0, right_pressed = 0, left_pressed = 0;

    SDL_Event e;
    int quit = 0;

    while (quit == 0)
    {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 255);
        SDL_RenderClear(renderer);
        
        while (SDL_PollEvent(&e))
        {
            switch ( e.type )
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        up_pressed = 1;
                        break;
                    case SDLK_DOWN:
                        // handle down arrow key pressed
                        down_pressed = 1;
                        break;
                    case SDLK_LEFT:
                        left_pressed = 1;
                        break;
                    case SDLK_RIGHT:
                        right_pressed = 1;
                        break;
                    case SDLK_SPACE:
                        // handle space key pressed
                        break;
                    // add cases for other keys as needed
                }
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        up_pressed = 0;
                        break;
                    case SDLK_DOWN:
                        // handle down arrow key pressed
                        down_pressed = 0;
                        break;
                    case SDLK_LEFT:
                        left_pressed = 0;
                        break;
                    case SDLK_RIGHT:
                        right_pressed = 0;
                        break;
                }
                break;    
            default:
                break;

            }

        }

        
        render(renderer, window, map);
        checkHorizontalIntersection(map, renderer);
        
        if (left_pressed && up_pressed)
        {
            direction -= UDEG;
            if (direction < 0) direction += P2I;
            pdx = 2 * cos(direction);
            pdy = 2 * sin(direction);

            playerX += pdx;
            playerY += pdy;
        }
        else if (right_pressed && up_pressed)
        {
            direction += UDEG;
            if (direction > P2I) direction -= P2I;
            pdx = 4 * cos(direction);
            pdy = 4 * sin(direction);
            playerX += pdx;
            playerY += pdy;
        }
        else if (up_pressed && down_pressed)
        {
            pdx = 0;
            pdy = 0;
        }
        else if (left_pressed)
        {
            // handle left arrow key pressed
             direction -= UDEG / 2;
            if (direction < 0) direction += P2I;;
        }
        else if (right_pressed)
        {
            // handle left arrow key pressed
            direction += UDEG / 2;
            if (direction > P2I) direction -= P2I;
            
        }
        else if (up_pressed)
        {
            pdx = 2 * cos(direction);
            pdy = 2 * sin(direction);
            playerX += pdx;
            playerY += pdy;
        }
        else if (down_pressed)
        {
            pdx = 2 * cos(direction);
            pdy = 2 * sin(direction);
            playerX -= pdx;
            playerY -= pdy;
        }
        














        // if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A])
        // {
        //     direction -= 1;
        //     if (direction < 0) direction += 360;
        //     pdx = 1 * cos(PI / 180 * direction);
        //     pdy = 1 * sin(PI / 180 * direction);

        //     playerX += pdx;
        //     playerY += pdy;
        // }

        SDL_RenderPresent(renderer);
    }




    //Destroy renderer
    SDL_DestroyRenderer(renderer);
    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
