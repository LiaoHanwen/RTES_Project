// algo.cpp

#include "algo.h"
#include "Arduino.h"
#include <vector>

#define PI 3.14

#define ALGO_WIFI_N 20 //N = 10 * n ,其中n为环境衰减因子，3.25-4.5
#define ALGO_WIFI_A -45  //接收机和发射机间隔1m时的信号强度

//#define DEBUG

Algo::Algo()
{
    pointNear = 0;
    pointFar = 0;
    kNear = 0;
    kFar = 0;
    mag = 1;
}

// return in cm
int Algo::wifi2Distance(int strengh)
{
    float iu = (float)(ALGO_WIFI_A - strengh) / (float)ALGO_WIFI_N;
    float distance = powf(10.0, iu);
    return distance * 100;
}

int Algo::distance2Point(int x, int y, const float *position, int refDistance)
{
    double distance = 12.5 * sqrt(sq(x - *position) + sq(y - *(position + 1)));
    int point;
    if (distance < refDistance)
    {
        if (distance < pointNear)
        {
            point = 80 - (pointNear - distance) * kFar;
        }
        else
        {
            point = 100 - (refDistance - distance) * kNear;
        }
    }
    else
    {
        if (distance > pointFar)
        {
            point = 80 - (distance - pointFar) * kFar;
        }
        else
        {
            point = 100 - (distance - refDistance) * kNear;
        }
    }

    if(point < 0)
        return 0;

    return point * mag;
}

void Algo::updatePara(float refDistance)
{
    if(refDistance == 0)
    {
        return;
    }
    float div3 = refDistance / 3.0;
    pointNear = refDistance - div3;
    pointFar = refDistance + div3;

    // 20 / (R/3)
    kNear = 60.0 / refDistance;

    // 80 / (2R/3)
    kFar = 120.0 / refDistance;

    mag = (float)(400 - refDistance) / 100.0;
    if(mag < 1)
    {
        mag = 1;
    }

#ifdef DEBUG
    Serial.printf("%f %f %f %f %f\n", pointNear, pointFar, kNear, kFar, mag);
#endif
}

// negative for turning left
int Algo::getAngle(float x, float y, const float *position)
{
    if(*(position + 1) == y)
    {
        if(*(position + 1) > y)
            return - PI / 2;
        else
            return PI / 2;
    } 
    else if(y > *(position + 1))  // 1, 2
    {
        return atan((*position - x) / (*(position + 1) - y)) * 180 / PI;
    }
    else if(x > *position) // 4
    {
        return atan((*position - x) / (*(position + 1) - y)) * 180 / PI + 180;
    }
    else  // 3
    {
        return atan((*position - x) / (*(position + 1) - y)) * 180 / PI - 180;
    }
}

void Algo::updatePosition(float *position, int direction, float pace)
{
    float rad = (float)direction / 180 * PI;
    *position += sin(rad) * pace;
    *(position + 1) += cos(rad) * pace;
}