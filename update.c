#include "update.h"


void checkHorizontalIntersection(const int map[9][9], SDL_Renderer *renderer)
{
    int xo, yo, dof, r, distT, lineH;
    double ray_x, ray_y, ray_direction = direction - ANGLE_30;
    if (ray_direction < 0) ray_direction += P2I; if (ray_direction > P2I) ray_direction -= P2I;
    int coY;
    int coX;

    for (r = 0; r < PPLANE_WIDTH; r++)
    {
        // horizontal
        double distH = 1000000;
        double hx = posX - OFFSETX_2D, hy = posY - OFFSETY_2D;
        dof = 0;
        double aTan = - 1 / tan(ray_direction);
        if ( ray_direction > PI)
        {
            ray_y = (((int)(posY - OFFSETY_2D) >> 6) << 6) - 0.001;
            ray_x = (posX - OFFSETX_2D) + ((posY - OFFSETY_2D) - ray_y) * aTan;
            yo = - GRID_SIZE;
            xo = -yo * aTan;
        }
        //vertically
        if ( ray_direction < PI)
        {
            ray_y = (((int)(posY - OFFSETY_2D) >> 6) << 6) + GRID_SIZE;
            ray_x = (posX - OFFSETX_2D) + ((posY - OFFSETY_2D) - ray_y) * aTan;
            yo = GRID_SIZE;
            xo = -yo * aTan;
        }
    
        //looking left or right
        if (ray_direction == P2I || ray_direction == P2I)
        {
            ray_x = posX - OFFSETX_2D;
            ray_y = posY - OFFSETY_2D;
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
                distH = dist(posX - OFFSETX_2D, posY - OFFSETY_2D, hx, hy, ray_direction);
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
        double distV = 1000000;
        double vx = posX - OFFSETX_2D, vy = posY - OFFSETY_2D;
        dof = 0;
        double nTan = -tan(ray_direction);
        if (ray_direction > PI_HALF && ray_direction < PI_HALF3)
        {
            ray_x = (((int) (posX - 700) >> 6) << 6) - 0.001;
            ray_y = (posY - OFFSETY_2D) + ((posX - OFFSETX_2D) - ray_x) * nTan;
            xo = -GRID_SIZE;
            yo = -xo * nTan;
        }
        // vertically
        if (ray_direction > PI_HALF3 || ray_direction < PI_HALF)
        {
            ray_x = (int) (((int)(posX - OFFSETX_2D) >> 6) << 6) + GRID_SIZE;
            ray_y = (posY - OFFSETY_2D) + ((posX - OFFSETX_2D) - ray_x) * nTan;
            xo = GRID_SIZE;
            yo = -xo * nTan;
        }

        // looking down or up
        if (ray_direction == PI_HALF || ray_direction == PI_HALF3)
        {
            ray_x = posX - OFFSETX_2D;
            ray_y = posY - OFFSETY_2D;
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
                distV = dist(posX - OFFSETX_2D, posY - OFFSETY_2D, vx, vy, ray_direction);
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
        SDL_RenderDrawLine(renderer, posX, posY, ray_x + OFFSETX_2D, ray_y + OFFSETY_2D);

        ray_direction += INCR;
        if (ray_direction < 0) ray_direction += P2I; if (ray_direction > P2I) ray_direction -= P2I;
    }
}

double dist(int ax, int ay, int bx, int by, double angle)
{
    return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) );
}
