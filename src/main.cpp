#include "Constants.h"

#define SENDER 1
#define RECEIVER 2

#define DEVICE RECEIVER 

#if TARGET == ESP_32
  #if DEVICE == SENDER
    #include "./ESPSender.h"
  #endif

  #if DEVICE == RECEIVER
    #include "./ESPReceiver.h"
  #endif
#elif TARGET == WINDOWS
  #include "./Test.h"
#endif



// #include <stdint.h>
// #include "Constants.h"
// #include "./Encryption/AES.h"
// #include "Utils.h"

// int main(){
//     uint8_t buffer[16] = {0x0,0x1,0x2,0x3,0x4,5,6,7,8,9,10,11,12,13,14,15};
//     int buffer_size = 16;

//     uint8_t key[16] = AES_KEY;
//     uint8_t init_vector[16] = AES_IV;

//     AES aes(AESKeyLength::AES_128);
//     uint8_t* cypher_text = aes.EncryptCBC(&buffer[0], buffer_size, &key[0], &init_vector[0]);

//     uint8_t key2[16] = AES_KEY;
//     uint8_t init_vector2[16] = AES_IV;

//     uint8_t* plain_text = aes.DecryptCBC(&cypher_text[0], buffer_size, &key2[0], &init_vector2[0]);
//     printArray(plain_text, 16);
// }