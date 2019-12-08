// move.cpp

#include "move.h"

move::move() : pin(p)
{
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
    pwm.begin();
}

move::~move() {}

void move::forward()
{
#ifdef DEBUG
    Serial.println("move forward");
#endif
    pwm.setPWM(3, 4096, 0);
    pwm.setPWM(2, 0, 4096);
    pwm.setPWM(1, 4096, 0);

    pwm.setPWM(0, 0, 4000);
}

void move::stop()
{
#ifdef DEBUG
    Serial.println("stop");
#endif
    pwm.setPWM(2, 0, 4096);
    pwm.setPWM(1, 0, 4096);
}