#include "WiFi.h"
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"
#include <SPI.h>
#include <LoRa.h>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include <WiFi.h>
#include <DNSServer.h>

const char *ssid = "FAEL-2.4GHz";
const char *password = "Woody1905";

int counter = 0;
unsigned long timestamp = millis();
bool zender = true;
String lastMessage = "";

AsyncWebServer server(80);
DNSServer dnsServer;

class CaptiveRequestHandler : public AsyncWebHandler
{
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request)
  {
    // request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request)
  {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print("<!DOCTYPE html><html><head><title>Captive Portal</title></head><body>");
    response->printf("<p>Go to <a href='http://%s'>this link</a></p>", WiFi.softAPIP().toString().c_str());
    response->print("</body></html>");
    request->send(response);
  }
};

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

  if (root.success())
  {
    if (root.containsKey("LoRaSpreadFactor"))
    {
      LoRa.setSpreadingFactor(std::atoi(root["LoRaSpreadFactor"]));
    }
    if (root.containsKey("txPower"))
    {
      LoRa.setTxPower(std::atoi(root["txPower"]));
    }
    {
      LoRa.setSpreadingFactor(std::atoi(root["LoRaSpreadFactor"]));
    }
    if (root.containsKey("bandwidth"))
    {
      LoRa.setSignalBandwidth(static_cast<int>(std::atof(root["bandwidth"]) * 1000));
    }
    if (root.containsKey("codingRate"))
    {
      Serial.println(std::atoi(root["codingRate"]));
      LoRa.setCodingRate4(std::atoi(root["codingRate"]));
    }
    if (root.containsKey("crc") && root["crc"] == "true")
    {
      Serial.println("CRC enabled");
      LoRa.enableCrc();
    }
    else
    {
      Serial.println("CRC dsisabled");
      LoRa.disableCrc();
    }
    if (root.containsKey("type"))
    {
      zender = root["type"] == "Transmitter";
    }
  }

  LoRa.end();
  if (!LoRa.begin(433E6))
  {
    Serial.println("Error");
  }

  Serial.println(LoRa.getSignalBandwidth());
  Serial.println(LoRa.getSpreadingFactor());
}

void setup()
{
  Serial.begin(115200);

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi..");
  // }

  // Serial.println(WiFi.localIP());

  LoRa.setPins(5, 14, 2);

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  // Load the config
  loadConfig();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(WiFi.macAddress().c_str());

  // Serve main application
  server.serveStatic("/", SPIFFS, "/frontend/");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/frontend/index.html", "text/html"); });

  // Serve the API
  server.on("/api/config", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    // Send back the current configuration of the ESP32, which is basically the one saved to SPIFFS
    if(SPIFFS.exists("/config/config.json")) {
      Serial.println("Sending normal config");
      request->send(SPIFFS, "/config/config.json", "application/json");
    }  else {
      Serial.println("Sending default config");
      request->send(SPIFFS, "/config/default.json", "application/json");
    } });

  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    // Send back the LoRa status
    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["SNR"] = LoRa.packetSnr();
    root["RSSI"] = LoRa.packetRssi();
    root["time"] = millis() - timestamp;
    
    if (!zender) {
      root["lastMessage"] = lastMessage;
    } else {
      root["counter"] = counter;
    }

    String result;
    root.prettyPrintTo(result);

    request->send(200, "application/json", result.c_str()); });

  server.on(
      "/api/config", HTTP_PATCH, [](AsyncWebServerRequest *request) {},
      NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
      File configFile = SPIFFS.open("/config/config.json", "w");
      configFile.write(data, len);
      configFile.close();
      loadConfig(); 
      
      request->send(200, "application/json", "{}"); });

  server.on("/api/config", HTTP_OPTIONS, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", ""); });

  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP

  server.begin();
}

void loop()
{
  dnsServer.processNextRequest();

  if (zender)
  {
    if (millis() - timestamp > 1000)
    {
      timestamp = millis();
      Serial.print("Sending packet: ");
      Serial.print("hello ");
      Serial.print(counter);
      Serial.println(';');

      // send packet
      LoRa.beginPacket();
      LoRa.print("hello ");
      LoRa.print(counter);
      LoRa.print(';');
      LoRa.endPacket();

      counter++;
    }
  }
  else
  {
    // try to parse packet
    int packetSize = LoRa.parsePacket(0);
    LoRa.clearWriteError();
    LoRa.flush();
    LoRa.setTimeout(10000);
    if (packetSize)
    {
      timestamp = millis();
      // received a packet
      Serial.print("Received packet (size ");
      Serial.print(packetSize);
      Serial.print(") '");

      // read packet

      // while (LoRa.available())
      // {
      lastMessage = LoRa.readStringUntil(';');
      Serial.print(lastMessage);
      // }

      // print RSSI of packet
      Serial.print("' with RSSI ");
      Serial.print(LoRa.packetRssi());
      Serial.print(" and SNR ");
      Serial.println(LoRa.packetSnr());
    }
    else
    {
      // LoRa.end();
      // if (!LoRa.begin(433E6))
      // {
      //   Serial.println("Error");
      // }
    }
  }
}
