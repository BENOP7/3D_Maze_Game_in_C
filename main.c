#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"
#include "texture.ppm"
#include "wall.ppm"


// Player's coordinate
float playerX;
float playerY;
float pdx, pdy;
float direction;

//tables
double *cosine;
double *sine;
double *tangent;
double *aTan;

//world
int worldmap[GRID_NUM][GRID_NUM];
// int texture[1024];

float dist(int ax, int ay, int bx, int by)
{
    return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) );
}

void render3D(SDL_Renderer *renderer, int hideMap)
{
    int mx, my, dof;
    float distT, lineH;
    float ra = direction - ANGLE_30; if (ra < 0) ra += P2I;
    float rx, ry, xo, yo;
    float distV, distH;
    float vx, vy , hx, hy;
    for (int r = 0; r < PPLANE_WIDTH; r++)
    {
        dof = 0;
        float atann = - 1 / tan(ra);

        distV = distH = 1000000;

        vx = hx = playerX - OFFSETX_2D;
        vy = hy = playerY - OFFSETY_2D;
        
        if (ra > PI && ra < P2I)
        {
            ry = (((int) (playerY - OFFSETY_2D) >> 6) << 6) - 0.0001;
            rx = playerX - OFFSETX_2D + (playerY - OFFSETY_2D - ry) * atann;
            yo = - GRID_SIZE;
            xo = - yo * atann;
        }
        if (ra > 0 && ra < PI)
        {
            ry = (((int) (playerY - OFFSETY_2D) >> 6) << 6) + GRID_SIZE;
            rx = playerX - OFFSETX_2D + (playerY - OFFSETY_2D - ry) * atann;
            yo = GRID_SIZE;
            xo = - yo * atann;
        }
        if (ra == PI || ra == 0 || ra == P2I)
        {
            rx = playerX - OFFSETX_2D;
            ry = playerY - OFFSETY_2D;
            dof = 8;
        }

        while (dof < 8)
        {            
            mx = ((int) rx) >> 6;
            my = ((int) ry) >> 6;
            if (mx >= 0 && my >= 0 && mx < GRID_NUM && my < GRID_NUM && worldmap[my][mx] > 0)
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
        float tann = - tan(ra);

        if (ra > PI_HALF && ra < PI_HALF3)
        {
            rx = (((int) (playerX - OFFSETX_2D) >> 6) << 6) - 0.0001;
            ry = playerY - OFFSETY_2D + (playerX - OFFSETX_2D - rx) * tann;
            xo = - GRID_SIZE;
            yo = - xo * tann;
        }
        if (ra < PI_HALF || ra > PI_HALF3)
        {
            rx = (((int) (playerX - OFFSETX_2D) >> 6) << 6) + GRID_SIZE;
            ry = playerY - OFFSETY_2D + (playerX - OFFSETX_2D - rx) * tann;
            xo = GRID_SIZE;
            yo = - xo * tann;
        }
        if (ra == PI_HALF || ra == PI_HALF3)
        {
            rx = playerX - OFFSETX_2D;
            ry = playerY - OFFSETY_2D;
            dof = 8;
        }
        
        while (dof < 8)
        {
            mx = ((int) rx) >> 6;
            my = ((int) ry) >> 6;
            if (mx >= 0 && my >= 0 && mx < GRID_NUM && my < GRID_NUM && worldmap[my][mx] > 0)
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
        int tx;
        float shade = 0.5;
        if (distV < distH)
        {          
            shade = 1;  
            distT = distV;
            rx = vx, ry = vy;
            tx = (int) (ry) % 64; // Calculate the grid offset
        }
        if (distH < distV)
        {
            distT = distH;
            rx = hx, ry = hy;
            tx = (int) (rx) % 64;
        }

        float beta = direction - ra; if (beta < 0) beta += P2I; if (beta > P2I) beta -= P2I;
        distT = distT * cos(beta);
            
        lineH = (DD * GRID_SIZE) / distT;

        float dy = 64.0 / (float) lineH;
        int ty_off = 0;
        if (lineH > PPLANE_HEIGHT) { ty_off = (lineH - PPLANE_HEIGHT) * 0.5; lineH = PPLANE_HEIGHT; }

        int upperoff = (PPLANE_HEIGHT - lineH) * 0.5;
        float ty = ty_off * dy;

        for (int y = 0; y <= lineH; y++)
        {
            SDL_SetRenderDrawColor(renderer, wall[(int) ty * 192 + (tx * 3)] * shade, wall[(int) ty * 192 + (tx * 3) + 1] * shade, wall[(int) ty * 192 + (tx * 3) + 2] * shade, 255);
            SDL_RenderDrawPoint(renderer, 50 + r, y + 60 + upperoff);
            ty += dy;
        }
        SDL_SetRenderDrawColor(renderer, 20, 150, 33, 255);
        SDL_RenderDrawLine(renderer, 50 + r, 60 + (PPLANE_HEIGHT + lineH) * 0.5, r + 50, 60 + PPLANE_HEIGHT);
        SDL_SetRenderDrawColor(renderer, 0x48, 0xA2, 0xFF, 255);
        SDL_RenderDrawLine(renderer, 50 + r, 60, r + 50, 60 + (PPLANE_HEIGHT - lineH) * 0.5);
        if (!hideMap)
        {
            SDL_SetRenderDrawColor(renderer, 200, 150, 133, 255);
            SDL_RenderDrawLine(renderer, playerX, playerY, rx + OFFSETX_2D, ry + OFFSETY_2D);
        }

        ra += INCR;
        if (ra > P2I) ra -= P2I;

    }
}

void render(SDL_Renderer * renderer, SDL_Window *window, int hideMap)
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


int main(int argc, char **argv)
{
    // The window we'll be rendering to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    int elapseTime, currentTime, previousTime = 0;

    for (int i = 0; i < GRID_NUM; i++)
    {
        for (int j = 0; j < GRID_NUM; j++)
        {
           
            worldmap[i][j] = 0;
        }
    }

    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return (EXIT_FAILURE);
    }
    if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            fprintf(stderr, "Could not open file! check file path or format.\
\nFilename: %s\n", argv[1]);
            return (EXIT_FAILURE);
        }

        int ch, n = 0;

        do {
            ch = fgetc(file);
            if (ch >= '0' && ch <= '9')
            {
                worldmap[n / GRID_NUM][n % GRID_NUM] = ch - '0';
                n++;
            }
            
        } while (ch != EOF || n < GRID_NUM * GRID_NUM);

        fclose(file);
    }
    // FILE *f = fopen("texture.txt", "r");
    // int ch, n = 0;
    // do {
    //     ch = fgetc(f);
    //     if (ch >= '0' && ch <= '9')
    //     {
    //         texture[n++] = ch - '0';
    //     }

    // } while (ch != EOF || n < 1024);

    // fclose(f);

    // for (int i = 0; i < n; i++)
    // {
    //         printf("%d", texture[i]);
    //     if ((i + 1) > 0 && (i + 1) % 8 == 0)
    //         printf("\n");
    // }


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
        free(cosine);
        free(sine);
        free(tangent);
        free(aTan);
        return EXIT_FAILURE;
    }
    
    for (int n = 0; n < 360; n++)
    {
        cosine[n] = cos(UDEG * n);    
        sine[n] = sin(UDEG * n);
        tangent[n] = tan(UDEG * n);
        aTan[n] = 1 / tangent[n];
    }

    for (int x = 0; x < GRID_NUM; x++)
    {
        for (int y = 0; y < GRID_NUM; y++)
        {
            printf("%d   ", worldmap[x][y]);
        }
        printf("\n");
    }

    //Default player position
    playerX = OFFSETX_2D + 144;
    playerY = OFFSETY_2D + 270;

    direction = UDEG * 60;
    pdx = 4 * cos(direction);
            pdy = 4 * sin(direction);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int up_pressed = 0, down_pressed = 0, right_pressed = 0, left_pressed = 0;
    int hideMap = 0, q_pressed = 0;

    
    int quit = 0;
    int time_d = 0;

    while (quit == 0)
    {
        currentTime = SDL_GetTicks64();
        elapseTime = currentTime - previousTime;
        previousTime = currentTime;
        SDL_SetRenderDrawColor(renderer, 0x78, 0x78, 0x78, 55);
        SDL_RenderClear(renderer);
        
        quit = handleEvents(&up_pressed, &down_pressed, &left_pressed, &right_pressed, &q_pressed);

        int xo = 0, yo = 0;
        if (pdx < 0) xo = - 30; else xo = 30;
        if (pdy < 0) yo = - 30; else yo = 30;
        int X = (playerX - OFFSETX_2D) / GRID_SIZE, Y = (playerY - OFFSETY_2D) / GRID_SIZE;
        int incX = (playerX - OFFSETX_2D + xo) / GRID_SIZE, decX = (playerX - OFFSETX_2D - xo) / GRID_SIZE;
        int incY = (playerY - OFFSETY_2D+ yo) / GRID_SIZE, decY = (playerY - OFFSETY_2D - yo) / GRID_SIZE;


              
        if (up_pressed && down_pressed)
        {
            pdx = 0;
            pdy = 0;
        }
        else if (up_pressed)
        {
            if (right_pressed)
            {
                direction += elapseTime * 0.2 * UDEG;
                if (direction > P2I)
                        direction -= P2I;
                pdx = elapseTime * 0.2 * cos(direction);
                pdy = elapseTime * 0.2 * sin(direction);
            }
            if (left_pressed)
            {
                direction -= elapseTime * 0.2 * UDEG;
                if (direction < 0)
                        direction += P2I;
                pdx = elapseTime * 0.2 * cos(direction);
                pdy = elapseTime * 0.2 * sin(direction);
            }
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
        {
            // handle left arrow key pressed
             direction -= elapseTime * 0.2 * UDEG;
            if (direction < 0)
                direction += P2I;
            pdx = elapseTime * 0.2 * cos(direction);
            pdy = elapseTime * 0.2 * sin(direction);
        }
        else if (right_pressed)
        {
            // handle right arrow key pressed
            direction += elapseTime * 0.2 * UDEG;
            if (direction > P2I)
                direction -= P2I;
            pdx = elapseTime * 0.2 * cos(direction);
            pdy = elapseTime * 0.2 * sin(direction);
        }
        else if( q_pressed)
        {
            time_d ++;
            if (time_d > 4)
            {
                time_d = 0;
                if (hideMap)
                    hideMap = 0;
                else
                    hideMap = 1;
                q_pressed = 0;
                
            }
        }

        render(renderer, window, hideMap);
        render3D(renderer, hideMap);

        SDL_RenderPresent(renderer);

        // SDL_Delay(5);
    }

    SDL_close(renderer, window, cosine, sine, tangent, aTan);   

    return 0;
}

int handleEvents(int *up_pressed, int *down_pressed, int *left_pressed,
                 int *right_pressed, int *q_pressed)
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
            switch (e.key.keysym.sym)
            {
            case SDLK_w:
                *up_pressed = 1;
                break;
            case SDLK_s:
                // handle down arrow key pressed
                *down_pressed = 1;
                break;
            case SDLK_a:
                *left_pressed = 1;
                break;
            case SDLK_d:
                *right_pressed = 1;
                // printf("Rightly setup\n");
                break;
            case SDLK_q:
                *q_pressed = 1;
                break;
            case SDLK_SPACE:
                // handle space key pressed
                break;
                // add cases for other keys as needed qqqq
            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
            case SDLK_w:
                *up_pressed = 0;
                break;
            case SDLK_s:
                // handle down arrow key pressed
                *down_pressed = 0;
                break;
            case SDLK_a:
                *left_pressed = 0;
                break;
            case SDLK_d:
                *right_pressed = 0;
                break;
            case SDLK_q:
                *q_pressed = 0;
                break;
            }
            break;
        default:
            break;
        }
    }

    return (quit);
}

void SDL_close(SDL_Renderer *renderer, SDL_Window *window, double *cosine,
               double *sine, double *tangent, double *aTan)
{
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
}
