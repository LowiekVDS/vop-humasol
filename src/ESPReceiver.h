#pragma once
#include "Constants.h"
#if TARGET == ESP_32
#include <SPI.h>
#include <LoRa.h>
#else
#include <iostream>
#endif
#include "Receiver.h"
#include "./Entries/Entries.h"

void setup()
{
  logInit();

// #if 1
//   receiver.m_buffer = new uint8_t[16]{0x80, 0xe7, 0xa3, 0x1f, 0xe1, 0x48, 0xbb, 0x37, 0xea, 0x27, 0x40, 0xa5, 0x8c, 0xa8, 0x20, 0x7c};
//   receiver.m_bufferSize = 16;
//   receiver.AESenabled(true);
// #else
//   receiver.m_buffer = new uint8_t[15]{0x01, 0x01, 0x19, 0x01, 0x01, 0x55, 0x01, 0x01, 0x0e, 0x01, 0x01, 0x3f, 0x02, 0x01, 0x2d};
//   receiver.m_bufferSize = 15;
//   receiver.AESenabled(false);
// #endif

  uint8_t* buffer = new uint8_t[6]{0x01, 0x01, 0x19, 0x03, 0x01, 0x00};
  uint8_t bufferSize = 6;

  Receiver receiver(buffer, bufferSize, EncryptionType::ENC_NONE);
  receiver.parse();
  receiver.process();
}

void loop()
{
}