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

DummyPhysicalLayer *dummyPHY = new DummyPhysicalLayer();

const uint8_t nrOfBufferLayers = 3;
BufferLayer *bufferLayers[nrOfBufferLayers]; 

// WebServer
ConfigurationServer *configServer = &ConfigurationServer::GetInstance();

void loadConfig()
{

  Serial.println("Loading configuration...");

  File configFile = SPIFFS.open("/config/config.json", "r");
  String config = configFile.readString();
  configFile.close();

  // Temporary
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

  Serial.print("Config: ");
  Serial.println(config.c_str());

  networkStack.loadConfig(&root);
}

void setup()
{
  // Communication
  if (DEBUG == 1)
  {
    Serial.begin(115200);
  }

  // Init the physicalLayer
  physicalLayer->init(433E6);

  // Init the buffer layers
  for (uint8_t i = 0; i < nrOfBufferLayers; i++) {
    bufferLayers[i] = new BufferLayer();
  }

  // Setup NetworkStack
  // networkStack.addLayer(&PhysicalLayer::GetInstance());

  networkStack.addLayer(dummyPHY);
  networkStack.addLayer(bufferLayers[0]);
  networkStack.addLayer(new EncryptionLayer(ENC_AES));
  networkStack.addLayer(bufferLayers[1]);
  networkStack.addLayer(new TransportLayer());
  networkStack.addLayer(bufferLayers[2]);
  networkStack.addLayer(&applicationLayer);

  // SPIFFS setup
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    throw "An Error has occurred while mounting SPIFFS";
  }

  // Load configuration
  loadConfig();

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
      
      loadConfig();
      
      request->send(200, "application/json", "{}"); });
  }
}

void loop()
{
  if (configServer->isInitialized())
  {
    configServer->dnsServer.processNextRequest();
  }

  // Sync buffer layers

  boolean activity = false;
  for (int8_t i = 0; i < nrOfBufferLayers; i++) {
    activity = bufferLayers[i]->step();
  }

  if (!activity) {
    // Go to sleep
    Serial.println("No activity anymore. Going to sleep");
    delay(1000);
    Serial.println("Receiving new data...");
    dummyPHY->OnReceive(10);
  }
}