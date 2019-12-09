// move.cpp

#include "move.h"
#include "Arduino.h"

Move::Move()
{
    pwm = Adafruit_PWMServoDriver();
    pwm.begin();
}

void Move::forward()
{
#ifdef DEBUG
    Serial.println("move forward");
#endif
    stall();
    pwm.setPWM(MOVE_AIN1, 0, 4096);
    pwm.setPWM(MOVE_AIN2, 4096, 0);
    pwm.setPWM(MOVE_PWMA, 0, MOVE_FORWARD_LEFT);

    pwm.setPWM(MOVE_BIN1, 0, 4096);
    pwm.setPWM(MOVE_BIN2, 4096, 0);
    pwm.setPWM(MOVE_PWMB, 0, MOVE_FORWARD_RIGHT);
    restart();
}

void Move::stop()
{
#ifdef DEBUG
    Serial.println("move stop");
#endif
    stall();
    pwm.setPWM(MOVE_AIN1, 0, 4096);
    pwm.setPWM(MOVE_AIN2, 0, 4096);

    pwm.setPWM(MOVE_BIN1, 0, 4096);
    pwm.setPWM(MOVE_BIN2, 0, 4096);
    restart();
}

void Move::left(int algle)
{
#ifdef DEBUG
    Serial.println("move left");
#endif
    stall();
    pwm.setPWM(MOVE_AIN1, 4096, 0);
    pwm.setPWM(MOVE_AIN2, 0, 4096);
    pwm.setPWM(MOVE_PWMA, 0, MOVE_TURN_LEFT);

    pwm.setPWM(MOVE_BIN1, 0, 4096);
    pwm.setPWM(MOVE_BIN2, 4096, 0);
    pwm.setPWM(MOVE_PWMB, 0, MOVE_TURN_RIGHT);
    restart();
}

void Move::right(int algle)
{
#ifdef DEBUG
    Serial.println("move right");
#endif
    stall();
    pwm.setPWM(MOVE_AIN1, 0, 4096);
    pwm.setPWM(MOVE_AIN2, 4096, 0);
    pwm.setPWM(MOVE_PWMA, 0, MOVE_TURN_LEFT);

    pwm.setPWM(MOVE_BIN1, 4096, 0);
    pwm.setPWM(MOVE_BIN2, 0, 4096);
    pwm.setPWM(MOVE_PWMB, 0, MOVE_TURN_RIGHT);
    restart();
}
