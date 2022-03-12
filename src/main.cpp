#include "Layers/Layers.h"
#include "Layers/LayerStack.h"
#include "Encryption/EncryptionType.h"
#include "ESPAsyncWebServer.h"
#include <DNSServer.h>
#include "WiFi.h"
#include "SPIFFS.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "WebServer/ConfigurationServer.h"

#define DEBUG 1

// Network stack
LayerStack networkStack;
ApplicationLayer applicationLayer;
PhysicalLayer *physicalLayer = &PhysicalLayer::GetInstance();

// WebServer
ConfigurationServer *configServer = &ConfigurationServer::GetInstance();

void setup()
{
  // Communication
  if (DEBUG == 1)
  {
    Serial.begin(115200);
  }

  // Init the physicalLayer
  physicalLayer->init(433E6);

  // Setup NetworkStack
  networkStack.addLayer(&PhysicalLayer::GetInstance());
  networkStack.addLayer(new TransportLayer());
  networkStack.addLayer(new EncryptionLayer(ENC_AES));
  networkStack.addLayer(&applicationLayer);

  // Load configuration
  // networkStack.loadConfig();

  // SPIFFS setup
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    throw "An Error has occurred while mounting SPIFFS";
  }

  // WiFi setup
  // TODO replace with digitalRead or something similar
  const bool enableWebserver = true;
  if (enableWebserver)
  {
    configServer->init();
    configServer->server.on(
        "/api/config", HTTP_PATCH, [](AsyncWebServerRequest *request) {},
        NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
      File configFile = SPIFFS.open("/config/config.json", "w");
      configFile.write(data, len);
      configFile.close();
      
      // TODO Reload LoRa config
      
      request->send(200, "application/json", "{}"); });
  }
}

void loop()
{
  if (configServer->isInitialized())
  {
    configServer->dnsServer.processNextRequest();
  }
}