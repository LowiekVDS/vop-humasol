#pragma once
#include "Constants.h"
#if TARGET == ESP_32
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
}

void loop() {
  
  sender.add(new BatteryLevelEntry(25));
  sender.add(new PumpStateEntry(PUMP_OPEN));

  sender.send();
  
}