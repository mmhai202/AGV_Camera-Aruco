#pragma once
#include "Config.h"
#include <Arduino.h>

class Encoder {
public:
  void begin();
  void start();
  void stop();
  void reset();
  int getL();
  int getR();
  static bool isCounting;
private:
  static void IRAM_ATTR isr1();
  static void IRAM_ATTR isr2();
  static volatile int encoderL;
  static volatile int encoderR;
};
