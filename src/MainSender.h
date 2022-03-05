#pragma once
#include "Constants.h"
#if TARGET == ESP32
#include <SPI.h>
#include <LoRa.h>
#else
#include <iostream>
#endif
#include "Sender.h"
#include "./Entries/Entries.h"

Sender sender;


void setup() {
  logInit();

  sender.add(new BatteryLevelEntry(25));
  sender.add(new BatteryLevelEntry(85));
  sender.add(new BatteryLevelEntry(14));
  sender.add(new BatteryLevelEntry(63));
  sender.add(new PumpLevelEntry(45));

  sender.send();
}

void loop() {
}


#if TARGET == GCC
int main(){
  setup();
  while (true){
    loop();
  }
}
#endif