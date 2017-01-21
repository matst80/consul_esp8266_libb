
//#include "Arduino.h"
#include "ConsulClient.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define ARG_DELIMITER ','

ESPConsulClient::ESPConsulClient(String serverAddress)
{
  _serverAddress = serverAddress;    
}

String join(const String strs[],  const int len) {
      String result = "";
      for (int i = 0; i < len; i++) {
        result += "\""+strs[i]+"\"" + ARG_DELIMITER;
      }
      return result.substring(0, result.length() - 1);
    }


bool ESPConsulClient::registerService(String id, String name)
{
    HTTPClient http;
    http.begin("http://"+_serverAddress+"/v1/agent/service/register"); //HTTP
    String ip = String(WiFi.localIP());
    
    
    String data = "{   \"ID\": \""+id+"\",   \"Name\": \""+name+"\",   \"Tags\": "+_tags+",   \"Address\": \""+ip+"\",   \"Port\": 80 }";
    int httpCode = http.sendRequest("PUT", data);
    http.end();
    return httpCode==200;
}


void ESPConsulClient::setTags(const String tags[], const int len) {
    _tags = "["+join(tags,len)+']';
}

String ESPConsulClient::getMQTTBase() 
{
    return getValue("mqttname");
}

String ESPConsulClient::getValue(string key)
{
    HTTPClient http;
    http.begin("http://"+_serverAddress+"/v1/kv/"+key); //HTTP
    
    int httpCode = http.sendRequest("GET", "");
    String ret = "";
    while (client.available()) {
        ret+=client.read();
    }
    

    delay(100);
    }
    http.end();
    
    return ret;
}
