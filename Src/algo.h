// algo.h
#include <vector>

using namespace std;

#ifndef ALGO_H
#define ALGO_H

class Algo
{
public:
    Algo();
    int wifi2Distance(int strength);
    int distance2Point(int x, int y, const float *position, int refDistance);
    void updatePara(int refDistance);
    int getAngle(float x, float y, const float *position);
    void updatePosition(float *position, int direction, float pace);
private:
    float mag;
    float pointNear;
    float pointFar;
    float kNear;
    float kFar;
};

#endif
