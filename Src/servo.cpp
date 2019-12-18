// servo.cpp

#include "servo.h"
#include "Arduino.h"

#define SERVO_ARGU 1.2
#define SERVO_LEFT_INIT 85
#define SERVO_RIGHT_INIT 90


Servo::Servo()
{
    pwm = Adafruit_PWMServoDriver();
    pwm.begin();
}

void Servo::setAngle(int angle)
{
    if(angle < 0)
    {
        angle = 0;
    }

    if(angle > 120)
    {
        angle = 120;
    }
    pwm.setPWM(8, 0, angle * SERVO_ARGU + SERVO_LEFT_INIT);
    pwm.setPWM(9, 0, (120 - angle) * SERVO_ARGU + SERVO_RIGHT_INIT);

    delay(200);
}