#include "ConfigApp.h"
#include "ArduinoJson.h"
#include "SPIFFS.h"
#include "Arduino.h"
#include <LoRa.h>
#include "../Entries/Entries.h"

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

            root["type"] = convertToString(configEntry->type, 5);
            root["password"] = convertToString(configEntry->password, 16);

            configFile = SPIFFS.open("/config/config.json", "w");

            String configAsString;
            root.printTo(configAsString);
            configFile.print(configAsString);

            configFile.close();

            // Reboot the ESP
            ESP.restart();
        }
        else if (entry->type == PONG)
        {
            // Received pong

            if (this->state == ConfigStates::CFG_SENT_PING)
            {
                this->state = ConfigStates::CFG_RECEIVED_PONG;
            }
        }
        else if (entry->type == PING)
        {
            PongEntry *pong = new PongEntry();

            this->addEntry(pong);
            this->flush();
        }

        it = entries.erase(it);
    }
}

void ConfigApp::sendConfig()
{

    if (this->state == ConfigStates::CFG_IDLE)
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
    case ConfigStates::CFG_SENT_CONFIG:
    default:
    {
        break;
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

        switch(firstThing) {
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
        break;
    }
    }
    // For configuration it just has to listen and stay awake
    LoRa.receive();
    return true;
}