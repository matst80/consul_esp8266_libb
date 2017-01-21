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
    void setTags(const String tags[], const int len);
    String join(const String strs[], const int len);
    String getMQTTBase();
    String getValue(string key);
private:
  String _serverAddress = "127.0.0.1:8500";
  String _tags = "[\"esp\",\"iot\"]";
};

//extern ESPConsulClient ConsulClient;

#endif
