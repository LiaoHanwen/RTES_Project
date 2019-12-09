// main.ino

#include "Arduino.h"
#include "move.h"

#define DEBUG

#ifdef DEBUG
#define SERIAL_BAUD_RATE 115200
#endif

Move move;

void setup() 
{
#ifdef DEBUG
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("serial debug start");
#endif 

}

void loop()
{
    move.forward();
    delay(1000);
    move.left(1000);
    delay(1000);
    move.right(1000);
    delay(1000);
    move.stop();
    delay(1000);
}
