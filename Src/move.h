// move.h

#ifndef MOVE_H
#define MOVE_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <QMC5883L.h>

#define MOVE_PWMA 0
#define MOVE_AIN2 1
#define MOVE_AIN1 2
#define MOVE_STBY 3
#define MOVE_BIN1 4
#define MOVE_BIN2 5
#define MOVE_PWMB 6

#define MOVE_FORWARD_LEFT 4000
#define MOVE_FORWARD_RIGHT 4000

#define MOVE_TURN_LEFT 3000
#define MOVE_TURN_RIGHT 3000

class Move
{
private:
    Adafruit_PWMServoDriver pwm;
    inline void stall() {pwm.setPWM(3, 0, 4096);};
    inline void restart() {pwm.setPWM(3, 4096, 0);};
public:
    Move();
    void forward();
    void left(QMC5883L *compass, int angle);
    void right(QMC5883L *compass, int angle);
	void left(int angle);
	void right(int angle);
	void left();
	void right();
	void stop();
};

#endif
