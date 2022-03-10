#include "LayerStack.h"
#include "../Constants.h"

void LayerStack::addEntry(TLVEntry* entry){
    m_entries.push_back(entry);
    m_bufferSize+=entry->size();
}

void LayerStack::flush(){
    uint8_t* payload = new uint8_t[m_bufferSize] {0}; // Sets buffer to 0;
    uint8_t* pointer = &payload[0];

    auto it = m_entries.begin();

    while (it != m_entries.end()){
        TLVEntry *entry = *it;
        entry->encode(pointer);
        delete entry;
        it = m_entries.erase(it);
    }

    m_topLayer->down(payload, m_bufferSize);
}

void LayerStack::setupStack(){
    m_PhysLayer = new PhysicalLayer(10e8);
    m_TranspLayer = new TransportLayer();
    m_EncrLayer = new EncryptionLayer(EncryptionType::ENC_AES);
    m_AppLayer = new ApplicationLayer();

    m_PhysLayer->setUpLayer(m_TranspLayer);

    m_TranspLayer->setDownLayer(m_PhysLayer);
    m_TranspLayer->setUpLayer(m_EncrLayer);

    m_EncrLayer->setDownLayer(m_TranspLayer);
    m_EncrLayer->setUpLayer(m_AppLayer);

    m_AppLayer->setDownLayer(m_EncrLayer);

    m_bottomLayer = m_PhysLayer;
    m_topLayer = m_AppLayer;
}
