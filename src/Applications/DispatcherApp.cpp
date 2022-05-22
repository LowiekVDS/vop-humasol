#include "DispatcherApp.h"
#include "../Entries/Entries.h"
#include "LoRa.h"
#include "SPIFFS.h"
#include "Layers/PhysicalLayer.h"

bool DispatcherApp::step()
{
    LoRa.receive();

    if (configuring)
    {
        return this->action == TLA_IDLE;
    }

    if (millis() - m_lastSent > 500000) // this->prm_send_interval)
    {

        m_lastSent = millis();

        runLoRaFeedback();
        runPump();
        runBattery();

        this->flush();
        return true;
    }
    return false;
}

void DispatcherApp::up(uint8_t *payload, uint8_t length)
{
    std::vector<TLVEntry *> entries = ApplicationLayer::extractEntries(payload, length);

    for (auto it = entries.begin(); it != entries.end();)
    {
        TLVEntry *entry = *it;

        if (entry->type == PING)
        {
            PongEntry *pong = new PongEntry();

            this->addEntry(pong);
            this->flush();
        }
        else if (entry->type == PONG)
        {
            if (configuring)
            {

                // Config has worked!
                File configFile = SPIFFS.open("/config/temp_config.json", "r");
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
        }
        else if (entry->type == TRANSPORTLAYER_E)
        {
            if (configuring)
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
        }
        else if (entry->type == LORA_CONFIG)
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

            configFile = SPIFFS.open("/config/temp_config.json", "w");

            String configAsString2;
            root.printTo(configAsString2);
            configFile.print(configAsString2);

            configFile.close();

            // // Reboot the ESP
            // ESP.restart();

            this->action = TLA_RESTART;
        }

        it = entries.erase(it);
    }
}

void DispatcherApp::loadConfig(JsonObject *config)
{
    if (config->containsKey("dispatcherSendInterval"))
    {
        this->prm_send_interval = std::atoi((*config)["dispatcherSendInterval"]);
    }
    if (config->containsKey("dispatcherPinFloatswitch"))
    {
        this->prm_pin_floatswitch = std::atoi((*config)["dispatcherPinFloatswitch"]);
    }
    if (config->containsKey("dispatcherInvert"))
    {
        this->prm_invert = (*config)["dispatcherInvert"] == "true";
    }
}

void DispatcherApp::runLoRaFeedback()
{
    // Send LoRa SNR and other information in a message

    int RSSI = LoRa.packetRssi();
    float SNR = LoRa.packetSnr();

    TLVEntry *entry = new LoRaFeedbackEntry(RSSI, SNR);
    this->addEntry(entry);
}

void DispatcherApp::runPump()
{
    int switch_value = digitalRead(this->prm_pin_floatswitch);

    Serial.println(switch_value);

    if (this->prm_invert)
    {
        switch_value = !switch_value;
    }

    TLVEntry *entry = new PumpStateEntry(switch_value ? PUMP_CLOSE : PUMP_OPEN);
    this->addEntry(entry);
}

void DispatcherApp::runBattery()
{
    // TODO
    return;
}