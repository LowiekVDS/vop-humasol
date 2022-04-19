#include "PingEntry.h"
#include "ArduinoJson.h"

TLVEntry* PingEntry::process(JsonObject* configuration)
{
    return TLVEntry::CreateFromType(PONG);
}