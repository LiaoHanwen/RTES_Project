// wifi.cpp

#include "wifi.h"
#include "Arduino.h"

#include "ESP8266WiFi.h"

#define DEBUG

Wifi::Wifi()
{
	
}

void Wifi::init()
{
#ifdef DEBUG
	Serial.println("start connect wifi");
#endif

	WiFi.begin(SSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
#ifdef DEBUG
		Serial.print("*");
#endif
	}
	
#ifdef DEBUG
	Serial.println("    WiFi connection Successful");
#endif
}

int Wifi::getWifiStrengh()
{
    return WiFi.RSSI();
}
