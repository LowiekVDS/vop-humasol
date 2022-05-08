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
#include "LoRa.h"

#include "Env.h"

// ----- Network stack & layers -----
LayerStack networkStack;
PhysicalLayer *physicalLayer = &PhysicalLayer::GetInstance();

const uint8_t nrOfBufferLayers = 3;
BufferLayer *bufferLayers[nrOfBufferLayers];

// ----- Applications -----
PingPongApp *pingPongApp = new PingPongApp();
DispatcherApp *dispatchApp = new DispatcherApp();
ControllerApp *controllerApp = new ControllerApp();
ConfigApp *configApp = new ConfigApp();
PongApp *pongApp = new PongApp();

// ----- WebServer -----
ConfigurationServer *configServer = &ConfigurationServer::GetInstance();

// ----- Global State -----
JsonObject *configuration;

void loadConfig()
{

  if (DEBUG)
  {
    Serial.println("Loading configuration...");
  }

  if (!SPIFFS.exists("/config/config.json"))
  {
    resetToDefaultConfig();
  }

  File configFile = SPIFFS.open("/config/config.json", "r");
  String config = configFile.readString();
  configFile.close();

  // Temporary
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

  configuration = &root;

  if (DEBUG)
  {

    Serial.print("Config: ");
    Serial.println(config.c_str());
  }

  networkStack.loadConfig(&root);
}

void resetToDefaultConfig()
{
  File defaultConfig = SPIFFS.open("/config/default.json");
  File config = SPIFFS.open("/config/config.json", "w");

  char *defaultConfigBuffer;

  defaultConfig.readBytes(defaultConfigBuffer, defaultConfig.size());
  config.write((uint8_t *)defaultConfigBuffer, defaultConfig.size());
  defaultConfig.close();
  config.close();
}

void setup()
{
  // Communication
  if (DEBUG == 1)
  {
    Serial.begin(115200);
  }

  // SPIFFS setup
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    throw "An Error has occurred while mounting SPIFFS";
  }

  // Init the physicalLayer
  physicalLayer->init(433E6);

  // Init the buffer layers
  for (uint8_t i = 0; i < nrOfBufferLayers; i++)
  {
    bufferLayers[i] = new BufferLayer(i);
  }

  // Load configuration
  loadConfig();

  // Based on configuration, setup network stack and reload config

  // Setup NetworkStack
  networkStack.addLayer(&PhysicalLayer::GetInstance());
  networkStack.addLayer(bufferLayers[0]);
  networkStack.addLayer(new EncryptionLayer(ENC_AES));
  networkStack.addLayer(bufferLayers[1]);
  networkStack.addLayer(new TransportLayer());
  networkStack.addLayer(bufferLayers[2]);

  if (configuration->containsKey("type"))
  {
    if ((*configuration)["type"] == "controller")
    {
      networkStack.addLayer(controllerApp);
    }
    else if ((*configuration)["type"] == "dispatcher")
    {
      networkStack.addLayer(dispatchApp);
    }
    else
    {
      networkStack.addLayer(configApp);
    }
  }
  else
  {
    networkStack.addLayer(configApp);
  }

  // Reload config as networkstack has changed
  loadConfig();

  // WiFi and config setup
  pinMode(GPIO_NUM_34, INPUT_PULLUP);
  if (!digitalRead(GPIO_NUM_34))
  {
    // Enable webserver

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

    // Reset to default config?
    resetToDefaultConfig();

    loadConfig();
  }

  pinMode(GPIO_NUM_32, OUTPUT);
  pinMode(GPIO_NUM_26, INPUT_PULLDOWN);
}

void loop()
{

  if (!digitalRead(GPIO_NUM_34))
  {
    ESP.restart();
  }

  if (configServer->isInitialized())
  {
    configServer->dnsServer.processNextRequest();
  }

  if (!networkStack.step())
  {
    // Serial.println("Going to deep sleep");
    LoRa.receive();
    // rtc_gpio_pulldown_en(GPIO_NUM_33);
    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 0);
  }
  else
  {
  }

  delay(10);
}