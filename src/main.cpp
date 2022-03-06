#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#include <SPI.h>
#include <LoRa.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"

const char *ssid = "FAEL-2.4GHz";
const char *password = "Woody1905";

int counter = 0;
unsigned long timestamp = millis();
bool zender = true;

AsyncWebServer server(80);

void loadConfig()
{

  if (!SPIFFS.exists("/config/config.json"))
  {
    File defaultConfig = SPIFFS.open("/config/default.json");
    File config = SPIFFS.open("/config/config.json", "w");

    char *defaultConfigBuffer;

    defaultConfig.readBytes(defaultConfigBuffer, defaultConfig.size());
    config.write((uint8_t *)defaultConfigBuffer, defaultConfig.size());
    defaultConfig.close();
    config.close();
  }

  File configFile = SPIFFS.open("/config/config.json", "r");
  String config = configFile.readString();
  configFile.close();

  DynamicJsonBuffer jsonBuffer;

  JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());
  Serial.println("Een configske doen eh");
  Serial.println(config);
  if (root.success())
  {
    if (root.containsKey("LoRaSpreadFactor"))
    {
      Serial.println(std::atoi(root["LoRaSpreadFactor"]));
      LoRa.setSpreadingFactor(std::atoi(root["LoRaSpreadFactor"]));
    }
    if (root.containsKey("bandwidth"))
    {
      Serial.println(static_cast<int>(std::atof(root["bandwidth"]) * 1000));
      LoRa.setSignalBandwidth(static_cast<int>(std::atof(root["bandwidth"]) * 1000));
    }
    if (root.containsKey("codingRate"))
    {
      LoRa.setCodingRate4(std::atoi(root["codingRate"]));
    }
    if (root.containsKey("crc") && root["crc"] == "true")
    {
      LoRa.enableCrc();
    }
    else
    {
      LoRa.disableCrc();
    }
    if (root.containsKey("type"))
    {
      Serial.println(root["type"].asString());
      zender = root["type"] == "Transmitter";
    }
  }

  LoRa.end();
  LoRa.begin(433E3);
}

void setup()
{
  Serial.begin(115200);

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  LoRa.setPins(5, 14, 2);

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  // Load the config
  loadConfig();

  // Serve main application
  server.serveStatic("/", SPIFFS, "/frontend/");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/frontend/index.html", "text/html"); });

  // Serve the API
  server.on("/api/config", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    // Send back the current configuration of the ESP32, which is basically the one saved to SPIFFS
    if(SPIFFS.exists("/config/config.json")) {
      Serial.println("config");
      request->send(SPIFFS, "/config/config.json", "application/json");
    }  else {
      Serial.println("default");
      request->send(SPIFFS, "/config/default.json", "application/json");
    } });

  server.on(
      "/api/config", HTTP_PATCH, [](AsyncWebServerRequest *request) {},
      NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
      File configFile = SPIFFS.open("/config/config.json", "w");
      configFile.write(data, len);
      configFile.close();
      loadConfig(); 
      
      request->send(200, "application/json", "{}"); });

    server.on("/api/config", HTTP_OPTIONS, [](AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "");
    });

  server.begin();
}

void loop()
{

  //if (millis() - timestamp > 1000) 
  //{
    timestamp = millis();
    if (zender)
    {
      Serial.print("Sending packet: ");
      Serial.println(counter);

      // send packet
      LoRa.beginPacket();
      LoRa.print("hello ");
      LoRa.print(counter);
      LoRa.endPacket();

      counter++;

      delay(50);
    }
    else
    {

      // try to parse packet
      int packetSize = LoRa.parsePacket();
      if (packetSize)
      {
        // received a packet
        Serial.print("Received packet '");

        // read packet
        while (LoRa.available())
        {
          Serial.print((char)LoRa.read());
        }

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.print(LoRa.packetRssi());
        Serial.print(" and SNR ");
        Serial.println(LoRa.packetSnr());
      }
    }
  //}
}