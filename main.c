#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265

// Screen dimension constants
const int SCREEN_WIDTH = 1360;
const int SCREEN_HEIGHT = 720;

const int GRID_SIZE = 64;
const int PLANE_SIZE2D = GRID_SIZE * 9;
const int PPLANE_WIDTH = 320;
const int PPLANE_HEIGHT = 200;
const int DD = 277;

int intersections[60];

// Player's coordinate
int playerX;
int playerY;
int pdx, pdy;
int direction;

void checkHorizontalIntersection(const int map[9][9], SDL_Renderer *renderer)
{
    int ray_x, ray_y, xo, yo, ray_direction = direction, dof, r;
    int coY;
    int coX;

    for (r = 0; r < 3; r+=3)
    {
        // horizontal
        dof = 0;
        float aTan = - 1 / tan(ray_direction * (PI / 180));
        if ( ray_direction > 180)
        {
            ray_y = ((playerY - 50) / 64) * 64 - 1;
            ray_x = (playerX - 700) + ((playerY -50) - ray_y) * aTan;
            yo = - GRID_SIZE;
            xo = -yo * aTan;
        }
        //vertically
        if ( ray_direction < 180)
        {
            ray_y = (((playerY - 50) >> 6) << 6) + GRID_SIZE;
            ray_x = (playerX - 700) + ((playerY -50) - ray_y) * aTan;
            yo = GRID_SIZE;
            xo = -yo * aTan;
        }
    
        //looking left or right
        if (ray_direction == 360 || ray_direction == 180)
        {
            ray_x = playerX - 700;
            ray_y = playerY - 50;
            dof = 8;
        }
        while (dof < 8)
        {
            coX = ray_x >> 6;
            coY = ray_y >> 6;
            if (coX >= 0 && coY >= 0 && coX < 9 && coY < 9 && map[coY][coX] > 0)
            {
                dof = 8;
            }
            else
            {
                ray_x += xo;
                ray_y += yo;
                dof++;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 222, 0, 222);

    SDL_RenderDrawLine(renderer, playerX, playerY, ray_x + 700, ray_y + 50);
    }

    for (r = 0; r < 3; r+=3)
    {
        // horizontal
        dof = 0;
        float nTan = -tan(ray_direction * (PI / 180));
        if ( ray_direction > 90 || ray_direction < 270)
        {
            ray_y = (((playerY - 50) >> 6) << 6) - 1;
            ray_x = (playerX - 700) + ((playerY -50) - ray_y) * nTan;
            xo = - GRID_SIZE;
            yo = -xo * nTan;
        }
        //vertically
        if ( ray_direction > 270 || ray_direction > 0)
        {
            ray_y = (((playerY - 50) >> 6) << 6) + GRID_SIZE;
            ray_x = (playerX - 700) + ((playerY -50) - ray_y) * nTan;
            xo = GRID_SIZE;
            yo = -xo * nTan;
        }
    
        //looking left or right
        if (ray_direction == 90 || ray_direction == 270)
        {
            ray_x = playerX - 700;
            ray_y = playerY - 50;
            dof = 8;
        }
        while (dof < 8)
        {
            coX = ray_x >> 6;
            coY = ray_y >> 6;
            if (coX>=0&& coY>=0 && coX < 9 && coY < 9 && map[coY][coX] > 0)
            {
                dof = 8;
            }
            else
            {
                ray_x += xo;
                ray_y += yo;
                dof++;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 222, 0, 255);

    SDL_RenderDrawLine(renderer, playerX, playerY, ray_x + 700, ray_y + 50);
    }

    // if (direction < 0)
    // {
    //     initIntersectionY = (playerY << 6) >> 6 - 1;
        
    //     coY = initIntersectionY / GRID_SIZE;

    //     initIntersectionX = playerX + (playerY - initIntersectionY) / tan((PI / 180) * direction);

    //     coX = initIntersectionX / GRID_SIZE;

        
    // }

    // intersections[0] = GRID_SIZE * coX;
    //     intersections[1] = (coY + 1) * GRID_SIZE;
    // if (map[coX][coY] == 1)    
}

int checkVerticalIntersection()
{

}

void render(SDL_Renderer * renderer, SDL_Window *window, const int map[9][9])
{
    
    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 170);

    SDL_RenderDrawLine(renderer, 110, 160, 430, 160);
    SDL_RenderDrawLine(renderer, 110, 360, 430, 360);
    SDL_RenderDrawLine(renderer, 110, 160, 110, 360);
    SDL_RenderDrawLine(renderer, 430, 160, 430, 360);
    for (int i = 700; i <= 700 + PLANE_SIZE2D; i += GRID_SIZE)
    {
        //Draw horizontal grid
        SDL_RenderDrawLine(renderer, 700, i - 650, 700 + PLANE_SIZE2D, i - 650);
        //Draw vertical grid
        SDL_RenderDrawLine(renderer, i, 50, i, 50 + PLANE_SIZE2D);
    }

    int idx;
    int idy;
    for (int i = 700; i < 700 + PLANE_SIZE2D; i += GRID_SIZE)
    {
        idx = (i - 700) / GRID_SIZE;
        for (int j = 50; j < 50 + PLANE_SIZE2D; j += GRID_SIZE)
        {
            idy = (j - 50) / GRID_SIZE;
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
        int idx = i - playerX + 5;

        for (int j = playerY - 5; j <= playerY + 4; j++)
        {
            SDL_Point holder = {i, j};
            points[10 * idx + j - playerY + 5] = holder;
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
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);

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
    playerX = 700 + 96;
    playerY = 50 + 225;

    direction = 300;
    pdx = 10 * cos(PI / 180 * direction);
    pdy = 10 * sin(PI / 180 * direction);

    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Hack to get window to stay up
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
                        playerX += pdx;;
                        playerY += pdy;
                        break;
                    case SDLK_DOWN:
                        // handle down arrow key pressed
                        playerX -= pdx;
                        playerY -= pdy;
                        break;
                    case SDLK_LEFT:
                        // handle left arrow key pressed
                        direction -= 1;
                        if (direction < 0) direction += 360;
                        pdx = 10 * cos(PI / 180 * direction);
                        pdy = 10 * sin(PI / 180 * direction);
                        break;
                    case SDLK_RIGHT:
                        // handle right arrow key pressed
                        direction += 1;
                        if (direction > 360 ) direction -= 360;
                        pdx = 10 * cos(PI / 180 * direction);
                        pdy = 10 * sin(PI / 180 * direction);
                        break;
                    case SDLK_SPACE:
                        // handle space key pressed
                        break;
                    // add cases for other keys as needed
                }
                break;
            default:
                break;

            }

        }

        
        render(renderer, window, map);
        checkHorizontalIntersection(map, renderer);

        SDL_RenderPresent(renderer);
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
