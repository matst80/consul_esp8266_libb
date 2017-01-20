
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "ConsulClient.h"

const char* ssid = "GetLost";
const char* password = "12bananer";
const char* mqtt_server = "10.10.10.1";
const char* serviceId = "MyTest1";
const char* serviceName = "MyTestName";


ESPConsulClient cclient("10.10.10.1:8500");

void setup() {

  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

}

void loop() {
    // wait for WiFi connection
    if(WiFi.status() == WL_CONNECTED) {

        cclient.registerService(serviceId, serviceName);
        //cclient.getMQTTName
    }

    delay(10000);
}

