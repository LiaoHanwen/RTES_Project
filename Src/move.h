// move.h

#ifndef MOVE_H
#define MOVE_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <QMC5883L.h>

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
    void forward(int distance);
	void left();
	void right();
	void stop();
};

#endif
