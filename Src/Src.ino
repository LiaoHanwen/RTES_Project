// main.ino

#include "Arduino.h"
#include "move.h"
#include "algo.h"
#include "wifi.h"

#define DEBUG

// setting for serial
#ifdef DEBUG
#define SERIAL_BAUD_RATE 115200
#endif

// setting for table
typedef int TABLE_TYPE;
#define TABLE_SIZE 64;

// talbe
TABLE_TYPE table[TABLE_SIZE][TABLE_SIZE];

// position of the car
TABLE_TYPE position[2];

// init varibles for libs
Move move;

void setup() 
{
#ifdef DEBUG
    // init serial
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("serial debug start");
#endif 

    // init position
    position[0] = TABLE_SIZE / 2;
    position[1] = TABLE_SIZE / 2;
}

void loop()
{
    int wifi = Wifi::getWifiStrengh();
    int distance = Algo::wifi2distance();

    int maxPoint = -100;
    int maxX = -1;
    int maxY = -1;
    for(int i = 0; i < TABLE_SIZE; ++i)
    {
        for(int j = 0; j < TABLE_SIZE; ++j)
        {
            table[i][j] += Algo::distance2Point(i, j, position, distance);
            if(table[i][j] > maxPoint)
            {
                maxPoint = table[i][j];
                maxX = i;
                maxY = j;
            }
        }
    }

    // todo move towards i,j
}
