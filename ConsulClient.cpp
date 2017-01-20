
//#include "Arduino.h"
#include "ConsulClient.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>



ESPConsulClient::ESPConsulClient(String serverAddress)
{
  _serverAddress = serverAddress;    
}


bool ESPConsulClient::registerService(String id, String name)
{
    HTTPClient http;
    http.begin("http://"+_serverAddress+"/v1/agent/service/register"); //HTTP
    String ip = String(WiFi.localIP());
    String data = "{   \"ID\": \""+id+"\",   \"Name\": \""+name+"\",   \"Tags\": [     \"crap\",     \"v1\"   ],   \"Address\": \""+ip+"\",   \"Port\": 80 }";
    int httpCode = http.sendRequest("PUT", data);
    http.end();
    return httpCode==200;
}

String ESPConsulClient::getMQTTName() 
{
    HTTPClient http;
    http.begin("http://"+_serverAddress+"/v1/agent/service/register"); //HTTP
    String ip = String(WiFi.localIP());
    String data = "ass";
    int httpCode = http.sendRequest("PUT", data);
    http.end();
    
    return String("/testgrejj/");
}
