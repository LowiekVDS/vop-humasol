#pragma once
#include "Constants.h"
#if TARGET == ESP32
#include <SPI.h>
#include <LoRa.h>
#else
#include <iostream>
#endif
#include "Receiver.h"
#include "./Entries/Entries.h"

Receiver receiver;


void setup() {
  logInit();
  
  uint8_t buffer[6] = {0x01, 0x01, 0x19, 0x02, 0x01,0x5f};
  
  receiver.parse(buffer, 6);
  receiver.process();
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
