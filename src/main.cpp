#include <SPI.h>
#include <LoRa.h>

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  // LoRa.setTxPower(10);

  LoRa.setPins(5, 14, 2);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println(LoRa.getSignalBandwidth());
  Serial.println(LoRa.getSpreadingFactor());
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(1000);
}

// #include <SPI.h>
// #include <LoRa.h>

// void setup() {
//   Serial.begin(9600);
//   while (!Serial);

//   Serial.println("LoRa Receiver");

//   LoRa.setPins(5, 14, 2);

//   if (!LoRa.begin(433E6)) {
//     Serial.println("Starting LoRa failed!");
//     while (1);
//   }
// }

// void loop() {
//   // try to parse packet
//   int packetSize = LoRa.parsePacket();
//   if (packetSize) {
//     // received a packet
//     Serial.print("Received packet '");

//     // read packet
//     while (LoRa.available()) {
//       Serial.print((char)LoRa.read());
//     }

//     // print RSSI of packet
//     Serial.print("' with RSSI ");
//     Serial.print(LoRa.packetRssi());
//     Serial.print(" and SNR ");
//     Serial.println(LoRa.packetSnr());
//   }
// }