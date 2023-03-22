#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"


// Player's coordinate
float playerX;
float playerY;
float pdx, pdy;
int direction;

//tables
double *cosine;
double *sine;
double *tangent;
double *aTan;

float dist(int ax, int ay, int bx, int by)
{
    return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) );
}

void checkIntersections(const int map[9][9], SDL_Renderer *renderer)
{
    int mx, my, dof, distT, lineH;
    float ra = direction - 30; if (ra < 0) ra += 360;
    float rx, ry, xo, yo;
    float distV, distH;
    float vx, vy , hx, hy;
    for (int r = 0; r < PPLANE_WIDTH; r++)
    {
        dof = 0;
        float atann = - aTan[(int) ra];

        distV = distH = 1000000;

        vx = hx = playerX - OFFSETX_2D;
        vy = hy = playerY - OFFSETY_2D;
        
        if (ra > 180 && ra < 360)
        {
            ry = (((int) (playerY - OFFSETY_2D) >> 6) << 6) - 0.0001;
            rx = playerX - OFFSETX_2D + (playerY - OFFSETY_2D - ry) * atann;
            yo = - GRID_SIZE;
            xo = - yo * atann;
        }
        if (ra > 0 && ra < 180)
        {
            ry = (((int) (playerY - OFFSETY_2D) >> 6) << 6) + GRID_SIZE;
            rx = playerX - OFFSETX_2D + (playerY - OFFSETY_2D - ry) * atann;
            yo = GRID_SIZE;
            xo = - yo * atann;
        }
        if (ra == 180 || ra == 0 || ra == 360)
        {
            rx = playerX - OFFSETX_2D;
            ry = playerY - OFFSETY_2D;
            dof = 8;
        }

        while (dof < 8)
        {            
            mx = ((int) rx) >> 6;
            my = ((int) ry) >> 6;
            if (mx >= 0 && my >= 0 && mx < 9 && my < 9 && map[my][mx] > 0)
            {
                dof = 8;
                hx = rx;
                hy = ry;
                distH = dist(playerX - OFFSETX_2D, playerY - OFFSETY_2D, hx, hy);
                
            }
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

        dof = 0;
        float tann = - tangent[(int)ra];

        if (ra > 90 && ra < 270)
        {
            rx = (((int) (playerX - OFFSETX_2D) >> 6) << 6) - 0.0001;
            ry = playerY - OFFSETY_2D + (playerX - OFFSETX_2D - rx) * tann;
            xo = - GRID_SIZE;
            yo = - xo * tann;
        }
        if (ra < 90 || ra > 270)
        {
            rx = (((int) (playerX - OFFSETX_2D) >> 6) << 6) + GRID_SIZE;
            ry = playerY - OFFSETY_2D + (playerX - OFFSETX_2D - rx) * tann;
            xo = GRID_SIZE;
            yo = - xo * tann;
        }
        if (ra == 90 || ra == 270)
        {
            rx = playerX - OFFSETX_2D;
            ry = playerY - OFFSETY_2D;
            dof = 8;
        }
        
        while (dof < 8)
        {
            mx = ((int) rx) >> 6;
            my = ((int) ry) >> 6;
            if (mx >= 0 && my >= 0 && mx < 9 && my < 9 && map[my][mx] > 0)
            {
                dof = 8;
                vx = rx;
                vy = ry;
                distV = dist(playerX - OFFSETX_2D, playerY - OFFSETY_2D, vx, vy);
                
            }
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }

        if (distV < distH)
        {
            distT = distV;
            rx = vx, ry = vy;
            SDL_SetRenderDrawColor(renderer, 45, 100, 154, 250);
        }
        if (distH < distV)
        {
            distT = distH;
            rx = hx, ry = hy;
            SDL_SetRenderDrawColor(renderer, 33, 68, 100, 250);
        }

        int beta = direction - ra;
        if (beta < 0) beta += 360;
        if (beta > 360) beta -= 360;

        distT = distT * cosine[beta];

        lineH = (DD * GRID_SIZE) / distT;
        if (lineH > PPLANE_HEIGHT) lineH = PPLANE_HEIGHT;

        ra += INCR;
        if (ra > 360) ra -= 360;

        
        SDL_RenderDrawLine(renderer, 50 + r, 60 + (PPLANE_HEIGHT - lineH) * 0.5, r + 50, 60 + (PPLANE_HEIGHT + lineH) * 0.5);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, playerX, playerY, rx + OFFSETX_2D, ry + OFFSETY_2D);
    }
}

void render(SDL_Renderer * renderer, SDL_Window *window, const int map[9][9])
{
    
    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 170);

    SDL_RenderDrawLine(renderer, 50, 60, 50 + PPLANE_WIDTH, 60);
    SDL_RenderDrawLine(renderer, 50 + PPLANE_WIDTH, 60, 50 + PPLANE_WIDTH, 60 + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer, 50, 60, 50, 60 + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer, 50, 60 + PPLANE_HEIGHT, 50 + PPLANE_WIDTH, 60 + PPLANE_HEIGHT);
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

    cosine = malloc(sizeof(*cosine) * 360);
    sine = malloc(sizeof(*sine) * 360);
    tangent = malloc(sizeof(*tangent) * 360);
    aTan = malloc(sizeof(*aTan) * 360);
    if (cosine == NULL || sine == NULL || tangent == NULL || aTan == NULL)
    {
        printf("Memory alloc error!");
        return EXIT_FAILURE;
    }
    
    for (int n = 0; n < 360; n++)
    {
        cosine[n] = cos(UDEG * n);    
        sine[n] = sin(UDEG * n);
        tangent[n] = tan(UDEG * n);
        aTan[n] = 1 / tangent[n];
    }

    int map[9][9] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 0, 1, 0, 0, 1, 1, 1 },
        { 1, 1, 0, 1, 0, 0, 1, 1, 1 },
        { 1, 1, 0, 1, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 1, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            printf("%d   ", map[x][y]);
        }
        printf("\n");
    }

    //Default player position
    playerX = OFFSETX_2D + 96;
    playerY = OFFSETY_2D + 225;

    direction = 300;
    pdx = 4 * cosine[direction];
    pdy = 4 * sine[direction];

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
        checkIntersections(map, renderer);
        
        if (left_pressed && up_pressed)
        {
            direction -= 1;
            if (direction < 0) direction += 360;
            pdx = 4 * cosine[direction];
            pdy = 4 * sine[direction];

            playerX += pdx;
            playerY += pdy;
        }
        else if (right_pressed && up_pressed)
        {
            direction += 1;
            if (direction > 360) direction -= 360;
            pdx = 4 * cosine[direction];
            pdy = 4 * sine[direction];
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
             direction -= 1;
            if (direction < 0)
                direction += 360;
            pdx = 4 * cosine[direction];
            pdy = 4 * sine[direction];
        }
        else if (right_pressed)
        {
            // handle left arrow key pressed
            direction += 1;
            if (direction > 360)
                direction -= 360;
            pdx = 4 * cosine[direction];
            pdy = 4 * sine[direction];
            
        }
        else if (up_pressed)
        {
            playerX += pdx;
            playerY += pdy;
        }
        else if (down_pressed)
        {
            playerX -= pdx;
            playerY -= pdy;
        }
    
        SDL_RenderPresent(renderer);

        SDL_Delay(20);
    }




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

    return 0;
}
