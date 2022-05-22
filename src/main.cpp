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

bool configMode = false;

void resetToDefaultConfig()
{

  if (DEBUG)
  {
    Serial.println("Resetting to default config...");
  }

  File defaultConfig = SPIFFS.open("/config/default.json");
  String configstring = defaultConfig.readString();
  File config = SPIFFS.open("/config/config.json", "w");

  char *defaultConfigBuffer;

  defaultConfig.readBytes(defaultConfigBuffer, defaultConfig.size());

  if (DEBUG)
  {
    Serial.println(configstring);
    Serial.println(defaultConfig.size());
  }

  Serial.println("wtf6");

  config.print(configstring);

  Serial.println("wtf7");
  defaultConfig.close();
  config.close();
}

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

  pinMode(GPIO_NUM_12, INPUT_PULLUP);
  Serial.println(digitalRead(GPIO_NUM_12));
  if (!digitalRead(GPIO_NUM_12))
  {
    configMode = true;
    // resetToDefaultConfig();
  }

  Serial.println("wtf8");
  // Init the physicalLayer
  physicalLayer->init(433E6);
  Serial.println("wtf9");
  // Init the buffer layers
  for (uint8_t i = 0; i < nrOfBufferLayers; i++)
  {
    bufferLayers[i] = new BufferLayer(i);
  }
  Serial.println("wtf10");

  // Setup NetworkStack
  networkStack.addLayer(&PhysicalLayer::GetInstance());
  networkStack.addLayer(bufferLayers[0]);
  networkStack.addLayer(new EncryptionLayer(ENC_AES));
  networkStack.addLayer(bufferLayers[1]);
  networkStack.addLayer(new TransportLayer());
  networkStack.addLayer(bufferLayers[2]);

  Serial.println("wtf11");

  loadConfig();

  if (configuration->containsKey("type") && !configMode)
  {

    if (configuration->containsKey("postConfig") && (*configuration)["postConfig"] == "true" ) {
      Serial.println("YEEEESSS");

      networkStack.addLayer(configApp);
      configApp->state = CFG_POSTCONFIG;


    } else if ((*configuration)["type"] == "contr")
    {
      networkStack.addLayer(controllerApp);
    }
    else if ((*configuration)["type"] == "dispa")
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

  Serial.println("wtf12");
  // Reload config as networkstack has changed
  loadConfig();

  if (configMode)
  {
    ledcSetup(0, 0, 8);
    ledcAttachPin(4, 0);
    ledcWrite(0, 128);
  }
  else
  {

    ledcSetup(0, 5000, 8);
    ledcAttachPin(4, 0);
    ledcWrite(0, 255);
  }

  // WiFi and config setup
  if (configMode)
  {
    // Enable webserver

    Serial.println("wtf1");

    configServer->server.on(
        "/api/config", HTTP_PATCH, [](AsyncWebServerRequest *request) {},
        NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
      
      Serial.println("TEST");
      File configFile = SPIFFS.open("/config/config.json", "w");
      configFile.write(data, len);
            Serial.println("TEST1");

      configFile.close();
            Serial.println("TEST1.5");

            // Now replace the top layer of the networkstack

            networkStack.removeLayer();
            networkStack.addLayer(configApp);

      configApp->sendConfig();
            Serial.println("TEST2");

      request->send(200, "application/json", "{}"); });
    Serial.println("wtf2");

    configServer->server.on(
        "/api/config/status", HTTP_GET, [](AsyncWebServerRequest *request)
        {

            DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["configStatus"] = String(configApp->state);

    String result;
    root.printTo(result);

      
      request->send(200, "application/json", result.c_str()); });

    Serial.println("wtf3");

    configServer->init();
    Serial.println("wtf4");

    // Reset to default config?
    // resetToDefaultConfig();

    loadConfig();
  }

  configServer->server.on(
      "/api/reset", HTTP_GET, [](AsyncWebServerRequest *request)
      {
        resetToDefaultConfig();
        ESP.restart(); });

  pinMode(GPIO_NUM_32, OUTPUT);
  pinMode(GPIO_NUM_26, INPUT);
}

void loop()
{

  if (!digitalRead(GPIO_NUM_12) && !configMode)
  {
    ESP.restart();
  }

  if (digitalRead(GPIO_NUM_12) && configMode)
  {
    configMode = false;
    ledcSetup(0, 5000, 8);
    ledcAttachPin(4, 0);
    ledcWrite(0, 255);
    ESP.restart();
  }

  if (configServer->isInitialized())
  {
    configServer->dnsServer.processNextRequest();
  }

  if (!networkStack.step())
  {

    Serial.println("Tis van da");
    Serial.println(configMode);

    if (((TopTerminalLayer *)networkStack.getTopLayer())->action == TLA_RESTART)
    {
      ESP.restart();
    }

    if (configMode)
    {

      if (configApp->state == CFG_SENT_CONFIG)
      {
        // Reload the configuration
        Serial.println("C1");
        loadConfig();
        Serial.println("C1.5");
        configApp->state = CFG_LOADED_CONFIG;
        Serial.println("C2");
      }
    }
    else
    {

      Serial.println("Going to deep sleep");

      LoRa.sleep();
      pinMode(14, INPUT);
      LoRa.end();

      esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, 0);
      esp_sleep_enable_ext0_wakeup((gpio_num_t)dispatchApp->prm_pin_floatswitch, !((bool)digitalRead(dispatchApp->prm_pin_floatswitch)));
      esp_sleep_enable_timer_wakeup(dispatchApp->prm_send_interval * 10 * 1000 * .8);
      esp_deep_sleep_start();
    }
  }
  else
  {
    LoRa.receive();
  }

  delay(10);
}