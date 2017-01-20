#ifndef EspConsul_h
#define EspConsul_h

#include "Arduino.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class ESPConsulClient
{

public:
    ESPConsulClient(String serverAddress);
    //~ESPConsulClient();
    bool registerService(String id, String name);
    String getMQTTName();
private:
  String _serverAddress;
};

//extern ESPConsulClient ConsulClient;

#endif
