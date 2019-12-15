// algo.h
#include <vector>

using namespace std;

#ifndef ALGO_H
#define ALGO_H
#define GRID_LENGTH
#define GRID_SIZE

class Algo
{
public:
    Algo();
    static float wifi2Distance(int strength);
	
    static int distance2Point(int x, int y, const int *position, int refDistance);
    
    void updateGrid(int x, int y, int rad);
    
    void updatePosition();
    
    static float angle2north();
    
    static pair<int, int> findMax(); 
private:
    
    static vector<vector<int>> grid; // record the grid
    
    static int init_x, init_y; // initial the position
    
    static int moveCount; // count the movement
    
    static pair<int, int> currPosition, prevPosition;
};

#endif
