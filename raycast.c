#include "raycast.h"

void checkHorizontalIntersection()
{
    int dof = 0;
    float atann = -1 / tan(ra);

    distV = distH = 1000000;

    vx = hx = playerX - OFFSETX_2D;
    vy = hy = playerY - OFFSETY_2D;

    if (ra > PI && ra < P2I)
    {
        ry = (((int)(playerY - OFFSETY_2D) >> 6) << 6) - 0.0001;
        rx = playerX - OFFSETX_2D + (playerY - OFFSETY_2D - ry) * atann;
        yo = -GRID_SIZE;
        xo = -yo * atann;
    }
    if (ra > 0 && ra < PI)
    {
        ry = (((int)(playerY - OFFSETY_2D) >> 6) << 6) + GRID_SIZE;
        rx = playerX - OFFSETX_2D + (playerY - OFFSETY_2D - ry) * atann;
        yo = GRID_SIZE;
        xo = -yo * atann;
    }
    if (ra == PI || ra == 0 || ra == P2I)
    {
        rx = playerX - OFFSETX_2D;
        ry = playerY - OFFSETY_2D;
        dof = 8;
    }

    while (dof < 8)
    {
        mx = ((int)rx) >> 6;
        my = ((int)ry) >> 6;
        if (mx >= 0 && my >= 0 && mx < GRID_NUM && my < GRID_NUM && worldmap[my][mx] > 0)
        {
            dof = 8;
            hx = rx, hy = ry;
            distH = dist(playerX - OFFSETX_2D, playerY - OFFSETY_2D, hx, hy);
        }
        else
        {
            rx += xo;
            ry += yo;
            dof++;
        }
    }
}
