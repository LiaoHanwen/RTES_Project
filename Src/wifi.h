// algo.h

#ifndef WIFI_H
#define WIFI_H

const char SSID[] = "ESPsoftAP_01";
const char PASSWORD[] = "12345678";

class Wifi
{
public:
    int getWifiStrengh();
	void init();
	Wifi();
};

#endif
