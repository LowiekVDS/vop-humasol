#include "ConfigApp.h"
#include "ArduinoJson.h"
#include "SPIFFS.h"
#include "Arduino.h"
#include <LoRa.h>
#include "../Entries/Entries.h"
#include "Layers/PhysicalLayer.h"

void ConfigApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;

        // Pump State Entry
        if (entry->type == LORA_CONFIG)
        {

            LoRaConfigEntry *configEntry = (LoRaConfigEntry *)entry;

            File configFile = SPIFFS.open("/config/config.json", "r");
            String config = configFile.readString();
            configFile.close();

            // Temporary
            DynamicJsonBuffer jsonBuffer;
            JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

            root["txPower"] = configEntry->txPower;
            root["LoRaSpreadFactor"] = configEntry->LoRaSpreadFactor;
            root["bandwidth"] = configEntry->bandwidth;
            root["crc"] = configEntry->crc;
            root["codingRate"] = configEntry->codingRate;

            configFile = SPIFFS.open("/config/config.json", "w");

            String configAsString;
            root.printTo(configAsString);
            configFile.print(configAsString);

            configFile.close();
        }
        else if (entry->type == CONFIG)
        {
            ConfigEntry *configEntry = (ConfigEntry *)entry;
            File configFile = SPIFFS.open("/config/config.json", "r");
            String config = configFile.readString();
            configFile.close();

            // Temporary
            DynamicJsonBuffer jsonBuffer;
            JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

            Serial.println("TTDSFDSFAD");
            Serial.println(convertToString(configEntry->type, 5));

            root["postConfig"] = "true";

            configFile = SPIFFS.open("/config/config.json", "w");

            String configAsString;
            root.printTo(configAsString);
            configFile.print(configAsString);

            configFile.close();

            root["type"] = convertToString(configEntry->type, 5);
            root["password"] = convertToString(configEntry->password, 16);
             root["postConfig"] = "false";

            configFile = SPIFFS.open("/config/temp_config.json", "w");

            String configAsString2;
            root.printTo(configAsString2);
            configFile.print(configAsString2);

            configFile.close();

            // // Reboot the ESP
            // ESP.restart();

            this->action = TLA_RESTART;
        }
        else if (entry->type == PONG)
        {
            // Received pong

            Serial.println("TIS VAN DAT EH HET WERKT");
            Serial.println(this->state);

            if (this->state == ConfigStates::CFG_SENT_PING)
            {
                this->state = ConfigStates::CFG_RECEIVED_PONG;
            }
            else if (this->state == CFG_SLAVE_SENT_PING)
            {
                Serial.println("DADADADA");
                // Config has worked!
                File configFile = SPIFFS.open("/config/temp_config.json", "r");
                String config = configFile.readString();
                configFile.close();

                // Temporary
                DynamicJsonBuffer jsonBuffer;
                JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

                root["postConfig"] = "false";

                configFile = SPIFFS.open("/config/config.json", "w");

                String configAsString;
                root.printTo(configAsString);
                configFile.print(configAsString);
                configFile.close();


                Serial.println("POP");
                this->action = TLA_RESTART;
            }
        }
        else if (entry->type == TRANSPORTLAYER_E)
        {
            if (this->state == CFG_SLAVE_SENT_PING)
            {
                // Config has not worked! Reset to defaults...
                Serial.println("Resetting to default settings...");

                // Config has worked!
                File configFile = SPIFFS.open("/config/default.json", "r");
                String config = configFile.readString();
                configFile.close();

                // Temporary
                DynamicJsonBuffer jsonBuffer;
                JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

                configFile = SPIFFS.open("/config/config.json", "w");

                String configAsString;
                root.printTo(configAsString);
                configFile.print(configAsString);
                configFile.close();

                this->action = TLA_RESTART;
            }

            this->state = ConfigStates::CFG_ERROR;
        }
        else if (entry->type == PING)
        {

            Serial.println("FDSAFDSAFDSFADS");
            Serial.println(this->state);
            PongEntry *pong = new PongEntry();

            this->addEntry(pong);
            this->flush();

            if (this->state == CFG_LOADED_CONFIG)
            {
                this->state = CFG_MASTER_SENT_PONG;
            }
        }

        it = entries.erase(it);
    }
}

void ConfigApp::sendConfig()
{

    if (this->state == ConfigStates::CFG_IDLE || this->state == ConfigStates::CFG_ERROR)
    {
        Serial.println("A1");
        PingEntry *ping = new PingEntry();
        this->addEntry(ping);
        Serial.println("A2");

        this->flush();
        Serial.println("A3");

        Serial.println("A4");

        this->state = ConfigStates::CFG_SENT_PING;
        Serial.println("A5");
    }
}

bool ConfigApp::step()
{
    switch (this->state)
    {
    case ConfigStates::CFG_IDLE:
    case ConfigStates::CFG_SENT_PING:
    default:
    {
        break;
    }
    case ConfigStates::CFG_POSTCONFIG:
    {

        File configFile = SPIFFS.open("/config/temp_config.json", "r");
        String config = configFile.readString();

        // Temporary
        DynamicJsonBuffer jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());

        PhysicalLayer *phy = &PhysicalLayer::GetInstance();
        Serial.println("D1");
        phy->loadConfig(&root);

        Serial.println("D2");
        PingEntry *ping = new PingEntry();

        Serial.println("D3");
        this->addEntry(ping);
        this->flush();

        Serial.println("D4");
        this->state = CFG_SLAVE_SENT_PING;
    }
    case ConfigStates::CFG_SENT_CONFIG:
    {
        return false;
    }
    case ConfigStates::CFG_RECEIVED_PONG:
    {
        File configFile = SPIFFS.open("/config/config.json", "r");
        String config = configFile.readString();
        configFile.close();

        Serial.println("B1");

        DynamicJsonBuffer jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject((const char *)config.c_str());
        Serial.println("B2");
        // Send LoRa Config and normal config
        LoRaConfigEntry *loraConfig = new LoRaConfigEntry(
            std::atoi(root["txPower"]),
            std::atoi(root["LoRaSpreadFactor"]),
            std::atoi(root["bandwidth"]),
            root["crc"] == "true",
            std::atoi(root["codingRate"]));
        Serial.println("B3");
        uint8_t type[5] = {0};
        uint8_t password[16] = {0};

        char firstThing = root["type"].asString()[0];

        switch (firstThing)
        {
        case 'c':
            memcpy(type, "dispa", 5);
            break;
        case 'd':
            memcpy(type, "contr", 5);
            break;
        }

        Serial.println("B4");
        memcpy(password, root["password"].asString(), 16);
        Serial.println("B5");
        ConfigEntry *normalConfig = new ConfigEntry(type, password);
        Serial.println("B6");
        // delete[] type;
        // delete[] password;
        Serial.println("B7");
        this->addEntry(loraConfig);
        this->addEntry(normalConfig);
        Serial.println("B8");
        this->flush();
        this->state = ConfigStates::CFG_SENT_CONFIG;
        Serial.println("B9");
        break;
    }
    }
    // For configuration it just has to listen and stay awake
    LoRa.receive();
    return action == TLA_IDLE;
}