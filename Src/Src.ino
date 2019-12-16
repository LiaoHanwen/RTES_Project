// main.ino

#include "Arduino.h"
#include "move.h"
#include "algo.h"
#include "wifi.h"

#include <string>

using namespace std;

//#define TEST
#define DEBUG
#define WIFI_DEBUG

// setting for serial
#ifdef DEBUG
#define SERIAL_BAUD_RATE 115200
#endif

// setting for table
typedef int TABLE_TYPE;
#define TABLE_SIZE 128

// talbe  6.25cm each
uint8_t table[TABLE_SIZE][TABLE_SIZE];

// position of the car
float position[2];

// direction
int direction = 0;

// init varibles for libs
Move g_move;
Wifi g_wifi;
Algo g_algo;
QMC5883L g_compass;

void setup()
{
#ifdef DEBUG
    // init serial
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("\n\n\nserial debug start");
#endif

    // init position
    position[0] = TABLE_SIZE / 2;
    position[1] = TABLE_SIZE / 2;

    // init compass
    g_compass.init();
    g_compass.setSamplingRate(128);

    // init wifi
    g_wifi.init();
#ifdef WIFI_DEBUG
    g_wifi.broadcast("start wifi debug");
#endif
}

void loop()
{
#ifdef TEST
    g_wifi.broadcast("test message");
    delay(1000);
#endif

#ifndef TEST

#ifdef DEBUG
    Serial.println("new loop");
#endif 

#ifdef WIFI_DEBUG
    char debugString[1024];
#endif

    int strengh = g_wifi.getWifiStrengh();
    int distance = g_algo.wifi2Distance(strengh);
    if(distance != 0)
    {
        g_algo.updatePara(distance);
    }
    
#ifdef WIFI_DEBUG
    sprintf(debugString, "strengh: %d, distance: %d\n", strengh, distance);
    g_wifi.broadcast(debugString);
#endif

    int maxPoint = -1;
    int maxX = -1;
    int maxY = -1;
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        for (int j = 0; j < TABLE_SIZE; ++j)
        {
            table[i][j] *= 0.9;
            table[i][j] += g_algo.distance2Point(i, j, position, distance);
            if (table[i][j] > maxPoint)
            {
                maxPoint = table[i][j];
                maxX = i;
                maxY = j;
            }
        }
    }

    int angle = g_algo.getAngle(maxX, maxY, position);
    int turn = angle - direction;

#ifdef WIFI_DEBUG
    sprintf(debugString, "max: %d, %d  max point: %d  angle: %d  turn: %d\n", maxX, maxY, maxPoint, angle, turn);
    g_wifi.broadcast(debugString);
#endif

    if (turn < 0)
    {
        g_move.left(-turn);
    }
    else
    {
        g_move.right(turn);
    }

    direction += turn;

    int pace = 1;
    g_move.forward(pace);
    g_algo.updatePosition(position, direction, pace);
#ifdef WIFI_DEBUG
    sprintf(debugString, "position: %f, %f  direction: %d\n\n", *position, *(position + 1), direction);
    g_wifi.broadcast(debugString);
#endif

#ifdef DEBUG
    delay(1000);
#endif

#endif
}
