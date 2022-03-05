#include "constants.h"
#ifndef DEBUG
#include <SPI.h>
#include <LoRa.h>
#else
#include <iostream>
#endif
#include "Sender.h"
#include "./Entries/Entries.h"

Sender sender;


void setup() {
  #ifndef DEBUG
  Serial.begin(SERIAL_BAUD_RATE);
  #else

  #endif
  sender.add(new BatteryLevelEntry(25));
  sender.add(new PumpLevelEntry(45));

  sender.send();
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