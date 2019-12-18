// servo.h

#ifndef SERVO_H
#define SERVO_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class Servo
{
private:
    Adafruit_PWMServoDriver pwm;
public:
    Servo();
    void setAngle(int angle);
};

#endif
