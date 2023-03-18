#include <math.h>


float dist(int ax, int ay, int bx, int by, float angle)
{
    return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) );
}
