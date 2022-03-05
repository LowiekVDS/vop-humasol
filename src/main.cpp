#define SENDER 1
#define RECEIVER 2

#define DEVICE SENDER 

#if DEVICE == SENDER
  #include "./MainSender.h"
#endif

#if DEVICE == RECEIVER
  #include "./MainReceiver.h"
#endif