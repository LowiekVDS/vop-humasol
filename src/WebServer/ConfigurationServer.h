#pragma once

#include "ESPAsyncWebServer.h"
#include "DNSServer.h"

class ConfigurationServer
{

private:
    bool initialized = false;

    /**
     * @brief Makes sure this class acts like a singleton
     */
    ConfigurationServer(void){};
    ConfigurationServer(const ConfigurationServer &) = delete;
    ConfigurationServer &operator=(const ConfigurationServer &) = delete;
    ConfigurationServer(ConfigurationServer &&) = delete;
    ConfigurationServer &operator=(ConfigurationServer &&) = delete;

public:
    AsyncWebServer server = AsyncWebServer(80);
    DNSServer dnsServer;

    /**
     * @brief Get the Instance object
     *
     * @return Server&
     */
    static ConfigurationServer &GetInstance()
    {
        static ConfigurationServer *singleton = new ConfigurationServer();
        return *singleton;
    }

    void init();

    inline bool isInitialized() {return this->initialized;};
};