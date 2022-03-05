#include "constants.h"
#ifndef DEBUG
#include <SPI.h>
#include <LoRa.h>
#else
#include <iostream>
#endif
#include "Receiver.h"
#include "./Entries/Entries.h"

Receiver receiver;

void battery_callback(BatteryLevelEntry* bat) {
  std::cout << "BatteryPacket Received!" << std::endl;
  bat->print();
    std::cout << std::endl;

}


void pump_callback(PumpLevelEntry* pump) {
  std::cout << "PumpPacket Received!" << std::endl;
  pump->print();
  std::cout << std::endl;
}

void setup() {
  #ifndef DEBUG
  Serial.begin(SERIAL_BAUD_RATE);
  #else

  #endif
  
  uint8_t buffer[6] = {0x01, 0x01, 0x19, 0x02, 0x01,0x2d};
  receiver.setBatteryLevelCallback(&battery_callback);
  receiver.setPumpLevelCallback(&pump_callback);
  receiver.parse(buffer, 6);
  receiver.print_results();
}

void loop() {
}


#ifdef DEBUG
int main(){
  setup();
  while (true){
    loop();
  }
}
#endif
