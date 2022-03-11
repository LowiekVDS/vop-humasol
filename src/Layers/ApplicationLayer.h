#pragma once
#include "TerminalLayer.h"
#include <vector>
#include "Entries/TLVEntry.h"
#include "ArduinoJson.h"

class ApplicationLayer : public TopTerminalLayer
{
private:
    /**
     * @brief TLVEntry entries. The buffer of entries to send (in a single packet)
     */
    std::vector<TLVEntry *> m_entries;

    /**
     * @brief The current size of all entries combined
     */
    uint8_t m_bufferSize;
    static std::vector<TLVEntry *> extractEntries(uint8_t *payload, uint8_t length);

public:
    ApplicationLayer() : TopTerminalLayer(){};
    void up(uint8_t *payload, uint8_t length) override;
    void down(uint8_t *payload, uint8_t length) override;

    void loadConfig(JsonObject jsonConfig);

    /**
     * @brief Add an entry to the buffer, waiting to be sent
     *
     * @param entry the TLVEntry to send
     */
    void addEntry(TLVEntry *entry);

    /**
     * @brief Actually sends the buffer as a packet
     */
    void flush();
};