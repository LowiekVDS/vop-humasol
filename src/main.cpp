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
#include "Applications/Applications.h"
#include "map"
#include "string"

#define DEBUG 1

// ----- Network stack & layers -----
LayerStack networkStack;
PhysicalLayer *physicalLayer = &PhysicalLayer::GetInstance();

const uint8_t nrOfBufferLayers = 3;
BufferLayer *bufferLayers[nrOfBufferLayers];

// ----- Applications -----
PingPongApp *pingPongApp = new PingPongApp();
PongApp *pongApp = new PongApp();

// std::map<std::string, Application *> applications;

Application *currentApplication = nullptr;

// ----- WebServer -----
ConfigurationServer *configServer = &ConfigurationServer::GetInstance();

// ----- Global State -----
JsonObject *configuration;

void loadConfig()
{

  Serial.println("Loading configuration...");

  File configFile = SPIFFS.open("/config/config.json", "r");
  String config = configFile.readString();
  configFile.close();

  // Temporary
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

  configuration = &root;

  Serial.print("Config: ");
  Serial.println(config.c_str());

  // if (root.containsKey("application"))
  // {

  //   if (applications.find(root["application"]) != applications.end())
  //   {
  //     currentApplication = applications[root["application"]];
  //   }
  // }

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
  for (uint8_t i = 0; i < nrOfBufferLayers; i++)
  {
    bufferLayers[i] = new BufferLayer();
  }

  // Setup NetworkStack
  networkStack.addLayer(&PhysicalLayer::GetInstance());
  networkStack.addLayer(bufferLayers[0]);
 // networkStack.addLayer(new EncryptionLayer(ENC_AES));
  // networkStack.addLayer(bufferLayers[1]);
  // networkStack.addLayer(new TransportLayer());
  // networkStack.addLayer(bufferLayers[2]);



  //networkStack.addLayer(pingPongApp);
  //currentApplication = pingPongApp;

  networkStack.addLayer(pongApp);
    currentApplication = pongApp;




  // SPIFFS setup
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    throw "An Error has occurred while mounting SPIFFS";
  }

  // Application setup
  // applications.insert(std::make_pair("PingPong", pingPongApp));

  // Load configuration
  loadConfig();

  // WiFi setup
  // TODO replace with digitalRead or something similar
  const bool enableWebserver = false;
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

  pinMode(15, OUTPUT);
}

void loop()
{
  if (configServer->isInitialized())
  {
    configServer->dnsServer.processNextRequest();
  }

  if (!networkStack.step() && !(currentApplication && !currentApplication->run()))
  {
    // Keep running
    digitalWrite(15, HIGH);
  }
  else
  {

    // Sleep
    digitalWrite(15, LOW);
  }
}