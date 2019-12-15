// algo.cpp

#include "algo.h"
#include "Arduino.h"
#include <vector>

#define ALGO_WIFI_N 32.5    //N = 10 * n ,其中n为环境衰减因子，3.25-4.5
#define ALGO_WIFI_A -45     //接收机和发射机间隔1m时的信号强度

#define GRID_LENGTH 400
#define GRID_SIZE 50

Algo::Algo(void) {
    int grid_h = GRID_LENGTH / GRID_SIZE;
    int grid_w = GRID_LENGTH / GRID_SIZE;

    grid.resize(grid_h);
    for (int i = 0; i < grid_h; ++i) {
        grid[i].resize(grid_w);
    }
    init_x = grid_h / 2;
    init_y = grid_w / 2;
    prevPosition.first = init_x;
    prevPosition.second = init_y;
}

float Algo::wifi2Distance(int strengh)
{
    float iu = (float)(ALGO_WIFI_A - strengh) / (float) ALGO_WIFI_N;
	float distance = powf(10.0, iu);
    return distance;
}

void Algo::updatePosition() {
    // TODO: pase in the movement;
    pair<int, int> newPosition;
    prevPosition = currPosition;
    currPosition = newPosition;
}

float Algo::angle2north() {
    return atan((currPosition.second - prevPosition.second) / (currPosition.first - prevPosition.first));
}

void Algo::updateGrid(int rx, int ry, int r) {
    double tol = 0.1;
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[0].size(); y++) {
            if ((double) abs(sq(x - rx) + sq(y - ry) - sq(r))< tol) {
                grid[x][y] += 1;
            }
        }
    }
}

pair<int, int> Algo::findMax() {
    int maxRSSI = -1;
    pair<int, int> coordinate(-1, -1);
    for (int x = 0; x < grid.size(); x++) {
        for (int y = 0; y < grid[0].size(); y++) {
            if (grid[x][y] > maxRSSI) {
                maxRSSI = grid[x][y];
                coordinate.first = x;
                coordinate.second = y;
            }
        }
    }
    return coordinate;
}


