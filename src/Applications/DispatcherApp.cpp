#include "DispatcherApp.h"
#include "../Entries/Entries.h"
#include "LoRa.h"
#include "SPIFFS.h"

bool DispatcherApp::step()
{
    LoRa.receive();
    if (millis() - m_lastSent > this->prm_send_interval)
    {

        m_lastSent = millis();

        runLoRaFeedback();
        runPump();
        runBattery();
        this->flush();
    }
    return 1;
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
        } else if (entry->type == LORA_CONFIG)
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