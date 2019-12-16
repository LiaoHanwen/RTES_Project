// wifi.h

#ifndef WIFI_H
#define WIFI_H

#include <WiFiUdp.h>

const char SSID[] = "Bingchen_Wang";
const char PASSWORD[] = "257@Gold#5Q";

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
