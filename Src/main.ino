// main.ino

#include "Arduino.h"
#include "move.h"

#define DEBUG

#ifdef DEBUG
#define SERIAL_BAUD_RATE 115200
#endif

move mo;

void setup() 
{
#ifdef DEBUG
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println("serial debug start");
#endif 

}

void loop()
{
    mo.forward();
    delay(1000);
    mo.stop();
    delay(1000);
}