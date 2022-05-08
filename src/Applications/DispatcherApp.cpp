#include "DispatcherApp.h"
#include "../Entries/Entries.h"
#include "LoRa.h"

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
    return 0;
}

void DispatcherApp::loadConfig(JsonObject* config) {
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

void DispatcherApp::runLoRaFeedback() {
    // Send LoRa SNR and other information in a message

    int RSSI = LoRa.packetRssi();
    float SNR = LoRa.packetSnr();

    TLVEntry * entry = new LoRaFeedbackEntry(RSSI, SNR);
    this->addEntry(entry);
}

void DispatcherApp::runPump()
{
    int switch_value = digitalRead(this->prm_pin_floatswitch);

    if (this->prm_invert) {
        switch_value = ! switch_value;
    }

    TLVEntry *entry = new PumpStateEntry(switch_value ? PUMP_CLOSE : PUMP_OPEN);
    this->addEntry(entry);
}

void DispatcherApp::runBattery()
{
 // TODO
  return;
}