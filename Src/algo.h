// algo.h

#ifndef ALGO_H
#define ALGO_H

class Algo
{
public:
    static int wifi2Distance(int strength);
    static int distance2Point(int x, int y, const int *position, int refDistance);
};

#endif
