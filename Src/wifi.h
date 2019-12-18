// wifi.h

#ifndef WIFI_H
#define WIFI_H

#include <WiFiUdp.h>

const char SSID[] = "RTES_TEST";
const char PASSWORD[] = "12345678";

class Wifi
{
public:
	int getWifiStrengh();
	void init();
	void broadcast(const char *message);
	Wifi();
private:
	WiFiUDP udp;
};

#endif
