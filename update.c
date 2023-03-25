#include "update.h"

double dist(int ax, int ay, int bx, int by)
{
    return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) );
}
