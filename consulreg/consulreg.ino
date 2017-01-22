
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include "ConsulClient.h" 
#include <PubSubClient.h>

const char* ssid = "GetLost";
const char* password = "12bananer";
const char* mqtt_server = "10.10.10.1";
char* consulId = "testesp";
char* serviceId = "/testesp";
char* serviceName = "Min test esp";
const int updatePort = 80;

WiFiClient espClient;
PubSubClient client(espClient);
ESPConsulClient cclient("10.10.10.1:8500");
long lastMsg = 0;
char msg[50];
bool registerd = false;


void setup() {
  Serial.begin(115200);
  delay(10);
  setupWifi();
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setupWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char msg[length];
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg[i] = payload[i];
  }
  Serial.println();
  if (strcmp(topic,getPath("update"))==0)
  {
    doupdate(msg);
  }
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("MQTT connecting...");
    // Attempt to connect
    if (client.connect(consulId)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //Serial.println(getPath("status"));
      client.publish(getPath("status"), "connected");
      // ... and resubscribe
      //client.subscribe("testskit");
      client.subscribe(getPath("update"));
      client.subscribe(getPath("reboot"));
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char* buildPath()
{
  char path[512];
  sprintf(path,"/firmware/%s.bin",consulId);
  return path;
}

void doupdate(char* url) {
        Serial.print("Updating firmware... ");
        char* mqttPath = getPath("updatestatus");
        client.publish(mqttPath, "Updating");
        Serial.println(buildPath());
        t_httpUpdate_return ret = ESPhttpUpdate.update(url,updatePort,buildPath());
        
        switch(ret) {
            case HTTP_UPDATE_FAILED:
                client.publish(mqttPath, "Update failed");
                Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                client.publish(mqttPath, "No updated");
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                Serial.println("HTTP_UPDATE_OK");
                break;
        }
}

char* getPath(char* func) {
  char ret[128];
  sprintf(ret,"%s/%s",serviceId,func);
  return ret;
}

void loop() {
    //Serial.println("New!!!!");
    // wait for WiFi connection
    if(WiFi.status() == WL_CONNECTED) {
        if (!registerd)
        {
          //cclient.registerService(consulId, serviceName);
          registerd = true;
        }
        
        
        if (!client.connected()) {
          reconnect();
          Serial.println("reconnect...");
          //client.publish(getPath("status"), "Reconnected");
        }
        
        long now = millis();
        if (now - lastMsg > 2000) {
         lastMsg = now;
         client.publish(getPath("ping"), "pong");
         Serial.println(getPath("ping"));
        }
        client.loop();
        //cclient.getMQTTName
    }
    else {
      Serial.println("no wifi");
      setupWifi();
    }

    delay(10);
}

