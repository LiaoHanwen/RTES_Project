// move.h

#include "Arduino.h"

#ifndef MOVE_H
#define MOVE_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class move
{
private:
    Adafruit_PWMServoDriver pwm;
public:
    move();
    ~move();
    void forward();
    void stop();
};

#endif
