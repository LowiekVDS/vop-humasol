#define SENDER 1
#define RECEIVER 2

#define DEVICE RECEIVER 

#if DEVICE == SENDER
  #include "./MainSender.h"
#endif

#if DEVICE == RECEIVER
  #include "./MainReceiver.h"
#endif