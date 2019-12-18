// ultra.cpp

#include "ultra.h"
#include "Arduino.h"

#define ULTRA_L_TRIG 12
#define ULTRA_L_ECHO 14
#define ULTRA_R_TRIG 15
#define ULTRA_R_ECHO 13


Ultra::Ultra()
{
    pinMode(ULTRA_L_TRIG, OUTPUT);
    pinMode(ULTRA_L_ECHO, INPUT);
    pinMode(ULTRA_R_TRIG, OUTPUT);
    pinMode(ULTRA_R_ECHO, INPUT);
}

void Ultra::mesureDistance()
{
    digitalWrite(ULTRA_L_TRIG, LOW);
    delay(5);

    digitalWrite(ULTRA_L_TRIG, HIGH);
    delay(10);
    digitalWrite(ULTRA_L_TRIG, LOW);

    long lDuration = pulseIn(ULTRA_L_ECHO, HIGH);
    lDistance= lDuration*0.034/2;

    digitalWrite(ULTRA_R_TRIG, LOW);
    delay(5);

    digitalWrite(ULTRA_R_TRIG, HIGH);
    delay(10);
    digitalWrite(ULTRA_R_TRIG, LOW);

    long rDuration = pulseIn(ULTRA_R_ECHO, HIGH);
    rDistance= rDuration*0.034/2;\

    delay(50);
}