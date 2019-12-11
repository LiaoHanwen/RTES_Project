// algo.cpp

#include "algo.h"
#include "Arduino.h"

int Algo::wifi2Distance(int strengh)
{
    // todo
    return 0;
}

int Algo::distance2Point(int x, int y, const int *position, int refDistance)
{
    double distance = sqrt(sq(x - *position) + sq(y - *(position + 1)));
    
    // todo
    return 0;
}