#include "parser.h"
#include <stdio.h>

int parseMap(char *filePath)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
        return (EXIT_FAILURE);

    int c, n = 0;

        do {
            c = fgetc(file);
            if (c >= '0' && c <= '9')
            {
                worldmap[n / GRID_NUM][n % GRID_NUM] = c - '0';
                n++;
            }
            
        } while (c != EOF || n < GRID_NUM * GRID_NUM);

        fclose(file);
        return (0);
}