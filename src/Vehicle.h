#pragma once
#include <Arduino.h>
#include "Encoder.h"
#include "Uart2.h"

class Vehicle {
public:
  int16_t speed;
  bool forward_10cm;
  bool turnleft_90deg;
  bool turnright_90deg;
  void begin(Encoder* encoder, Uart2* _uart2);
  void stop();
  void left(int16_t pwm);
  void right(int16_t pwm);
private:
  Encoder* _encoder;
  Uart2* _uart2;
};