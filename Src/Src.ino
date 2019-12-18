// main.ino

#include "Arduino.h"
#include "move.h"
#include "algo.h"
#include "wifi.h"
#include "servo.h"
#include "ultra.h"

#include <string>

using namespace std;

//#define TEST
//#define DEBUG
#define WIFI_DEBUG

// setting for serial
#ifdef DEBUG
#define SERIAL_BAUD_RATE 115200
#endif

// interrupt pins
#define INTERRUPT_PIN1 0
#define INTERRUPT_PIN2 16
#define INTERRUPT_PIN3 2

// wifi strengh terminal
#define WIFI_TERMINAL -40

// forward pace
#define PACE 8
// 6.25 * frac
#define FORWARD_ARGU 1.5

// setting for table
typedef uint16_t TABLE_TYPE;
#define TABLE_SIZE 128

// talbe  6.25cm each
TABLE_TYPE table[TABLE_SIZE][TABLE_SIZE];

// position of the car
float position[2];

// direction
int direction = 0;

// distance
int g_distance = 1000;
int g_lastDistance[2] = {0, 0};

// init varibles for libs
Move g_move;
Wifi g_wifi;
Algo g_algo;
Servo g_servo;
Ultra g_ultra;
QMC5883L g_compass;

void setup()
{
#ifdef DEBUG
    // init serial
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("\n\n\nserial debug start");
#endif

    // init interrupt pins
    pinMode(INTERRUPT_PIN1, INPUT);
    pinMode(INTERRUPT_PIN2, INPUT);
    pinMode(INTERRUPT_PIN3, INPUT);

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
    Serial.println(digitalRead(INTERRUPT_PIN1));
#endif

#ifndef TEST

#ifdef DEBUG
    Serial.println("new loop");
#endif

#ifdef WIFI_DEBUG
    char debugString[1024];
#endif

    int strengh = g_wifi.getWifiStrengh();

    if(strengh > WIFI_TERMINAL)
    {
#ifdef WIFI_DEBUG
        sprintf(debugString, "TERMINAL!!!!!!!!!!\n");
        g_wifi.broadcast(debugString);
        delay(1000);
#endif
        while(true)
        {
            yield();
        }
    }

    g_distance = g_algo.wifi2Distance(strengh);
    if (g_distance != 0)
    {
        g_algo.updatePara(g_distance);
    }

#ifdef WIFI_DEBUG
    sprintf(debugString, "strengh: %d, distance: %d", strengh, g_distance);
    g_wifi.broadcast(debugString);
    delay(1000);
#endif

    int maxPoint = -1;
    int maxAddPoint = -1;
    int maxX = -1;
    int maxY = -1;
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        for (int j = 0; j < TABLE_SIZE; ++j)
        {
            table[i][j] *= 0.8;
            int addPoint = g_algo.distance2Point(i, j, position, g_distance);
            table[i][j] += addPoint;
            if (table[i][j] > maxPoint)
            {
                maxAddPoint = addPoint;
                maxPoint = table[i][j];
                maxX = i;
                maxY = j;
            }
        }
    }

    int angle = g_algo.getAngle(maxX, maxY, position);
    int turn = angle - direction;

#ifdef WIFI_DEBUG
    sprintf(debugString, "max: %d, %d  max point: %d  add: %d  angle: %d  turn: %d", maxX, maxY, maxPoint, maxAddPoint, angle, turn);
    g_wifi.broadcast(debugString);
#endif

    // modify g_lastDistance
    int compareDistance = g_lastDistance[0] + g_lastDistance[1] / 2;
    g_lastDistance[0] = g_lastDistance[1];
    g_lastDistance[1] = g_distance;

    if(compareDistance - g_distance < float(PACE) * FORWARD_ARGU)
    {
        // change to new direction
        if (turn < 0)
            g_move.left(-turn);
        else
            g_move.right(turn);
        direction += turn;
    }

    // avoid
    g_ultra.mesureDistance();
    int lDistance = g_ultra.getLDistance();
    int rDistance = g_ultra.getRDistance();

    // do not turn left
    bool rPref = false;

    while((lDistance != 0 && lDistance < 10 * PACE) || (rDistance != 0 && rDistance < 10 * PACE)
        || digitalRead(INTERRUPT_PIN1) == LOW || digitalRead(INTERRUPT_PIN2) == LOW || digitalRead(INTERRUPT_PIN3) == LOW)
    {
        int angle = 30;
        for(; angle < 120; angle += 30)
        {
            g_servo.setAngle(angle);

            g_ultra.mesureDistance();
            lDistance = g_ultra.getLDistance();
            rDistance = g_ultra.getRDistance();

            if(lDistance > 10 * PACE && !rPref)
            {
                g_move.left(angle);
                g_servo.setAngle(0);
                break;
            }

            if(rDistance > 10 * PACE)
            {
                rPref = true;
                g_move.right(angle);
                g_servo.setAngle(0);
                break;
            }
        }

        if(angle == 150)
        {
            g_move.left(90);
            g_servo.setAngle(0);
        }
    }

    float forwardDistance = g_move.forward(PACE);

    g_algo.updatePosition(position, direction, forwardDistance);
#ifdef WIFI_DEBUG
    sprintf(debugString, "position: %f, %f  direction: %d  forward: %f\n", *position, *(position + 1), direction, forwardDistance);
    g_wifi.broadcast(debugString);
#endif

#ifdef DEBUG
    delay(1000);
#endif

#endif
}
