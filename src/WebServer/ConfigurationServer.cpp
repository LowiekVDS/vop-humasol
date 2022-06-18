#include "ConfigurationServer.h"
#include "assert.h"
#include "ESPAsyncWebServer.h"
#include <DNSServer.h>
#include "SPIFFS.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "CaptiveRequestHandler.h"
#include <WiFi.h>
#include <LoRa.h>

void ConfigurationServer::init()
{
  assert(!this->initialized);

  // const char *ssid = "FAEL-2.4GHz";
  // const char *password = "Woody1905";

  WiFi.mode(WIFI_AP);
  WiFi.softAP(WiFi.macAddress().c_str());
  // WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.println("Connecting to WiFi..");
  // }
  // Serial.print("IP Address is: ");
  // Serial.println(WiFi.localIP());

  // Serve main application
  this->server.serveStatic("/", SPIFFS, "/frontend/");
  this->server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(SPIFFS, "/frontend/index.html", "text/html"); });

  // Serve the API
  this->server.on("/api/config", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    // Send back the current configuration of the ESP32, which is basically the one saved to SPIFFS
    if(SPIFFS.exists("/config/config.json")) {
      request->send(SPIFFS, "/config/config.json", "application/json");
    }  else {
      request->send(SPIFFS, "/config/default.json", "application/json");
    } });

  this->server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    // Send back the LoRa status
    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["SNR"] = LoRa.packetSnr();
    root["RSSI"] = LoRa.packetRssi();
    root["time"] = millis();

    String result;
    root.prettyPrintTo(result);

    request->send(200, "application/json", result.c_str()); });

  // Required for CORS
  this->server.on("/api/config", HTTP_OPTIONS, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/plain", ""); });

  dnsServer.start(53, "*", WiFi.softAPIP());
  this->server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP

  this->server.begin();

  this->initialized = true;
}