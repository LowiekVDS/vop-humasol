# ESP32 transmitter/receiver code
## Compile Utilities
To facilitate compilation using either the *g++ compiler* and the *PlatformIO compiler*. Multiple build tasks were set up. When using one of those build tasks, the apropriate `#define TARGET`-macro's will be set, which will adapt all platform specific code like printing, ... 
## Sender / Receiver
To easily switch from sender to receiver code, you can simply change the `#define DEVICE`-macro in `main.cpp` to either `SENDER` or `RECEIVER`. The correct source code will be compiled and deployed.