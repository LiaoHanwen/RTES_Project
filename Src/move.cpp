// move.cpp

#include "move.h"
#include "Arduino.h"

#include <QMC5883L.h>

#define DEBUG

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

#define MOVE_FORWARD_CONS 113

#define MOVE_TURN_LEFT_CONS 11
#define MOVE_TURN_LEFT_INIT 90

#define MOVE_TURN_RIGHT_CONS 11
#define MOVE_TURN_RIGHT_INIT 90

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

void Move::right()
{
#ifdef DEBUG
    Serial.println("move right");
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

void Move::left()
{
#ifdef DEBUG
    Serial.println("move left");
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

void Move::left(QMC5883L *compass, int angle)
{
#ifdef DEBUG
    Serial.print("move right: ");
    Serial.println(angle);
#endif
	angle %= 360;
	int init = compass->readHeading();
	int target = init < angle ? (init - angle + 360) : (init - angle);
#ifdef DEBUG
    Serial.print("init: ");
    Serial.println(init);
	Serial.print("target: ");
    Serial.println(target);
#endif
	left();
	int head;
	do
	{
		head = compass->readHeading();
		yield();
#ifdef DEBUG
		Serial.print("head: ");
		Serial.println(head);
#endif
	} while(head < target - 5 || head > target + 5);
	
	stop();
}

void Move::right(QMC5883L *compass, int angle)
{
	angle %= 360;
	int head = compass->readHeading();
	
	left();
	while(head - compass->readHeading() > angle);
	stop();
}

void Move::left(int angle)
{
	left();
	delay(angle * MOVE_TURN_LEFT_CONS + MOVE_TURN_LEFT_INIT);
	stop();
}

void Move::right(int angle)
{
	right();
	delay(angle * MOVE_TURN_RIGHT_CONS + MOVE_TURN_RIGHT_INIT);
	stop();
}

void Move::forward(int grid)
{
    forward();
    delay(grid * MOVE_FORWARD_CONS);
    stop();
}