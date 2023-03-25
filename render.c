#include "render.h"
#include "wall.ppm"

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



/**
 * render - renders the whole world on the window
 * @renderer: the SDL renderer
 * @hideMap: render map decision flag (boolean)
 *
 */
void render(SDL_Renderer * renderer, int hideMap)
{
    /* Draw boundary lines for 3D rendering */
    SDL_SetRenderDrawColor(renderer, 80,32, 16, 255);

    SDL_RenderDrawLine(renderer, 50, 60, 50 + PPLANE_WIDTH, 60);
    SDL_RenderDrawLine(renderer, 50 + PPLANE_WIDTH, 60, 50 + PPLANE_WIDTH, 60 + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer, 50, 60, 50, 60 + PPLANE_HEIGHT);
    SDL_RenderDrawLine(renderer, 50, 60 + PPLANE_HEIGHT, 50 + PPLANE_WIDTH, 60 + PPLANE_HEIGHT);

    if (!hideMap)
        renderMap(renderer);
}

/**
 * renderMap - draw the 2D map of the world
 * @renderer: the SDL renderer
 *  
 */
void renderMap(SDL_Renderer *renderer)
{
    int idx;
    int idy;

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

        drawPlayer(renderer);
}

/**
 * drawPlayer - draw the dot representing the player on 2D map
 * @renderer: the SDL renderer
 *  
 */
void drawPlayer(SDL_Renderer *renderer)
{
    int idx, idy;
    SDL_Point points[100];

    SDL_SetRenderDrawColor(renderer, 15, 25, 165, 200);

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