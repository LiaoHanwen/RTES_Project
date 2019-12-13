// algo.cpp

#include "algo.h"
#include "Arduino.h"

#define ALGO_WIFI_N 32.5    //N = 10 * n ,其中n为环境衰减因子，3.25-4.5
#define ALGO_WIFI_A -45     //接收机和发射机间隔1m时的信号强度

float Algo::wifi2Distance(int strengh)
{
    float iu = (float)(ALGO_WIFI_A - strengh) / (float) ALGO_WIFI_N;
	float distance = powf(10.0, iu);
    return distance;
}

int Algo::distance2Point(int x, int y, const int *position, int refDistance)
{
    double distance = sqrt(sq(x - *position) + sq(y - *(position + 1)));
    
    // todo
    return 0;
}