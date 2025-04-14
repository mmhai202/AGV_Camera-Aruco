#pragma once
#include <Arduino.h>

class Vehicle {
public:
  uint8_t speed;
  void begin();
  void stop();
  void forward  (uint8_t pwm);
  void back     (uint8_t pwm);
  void left     (uint8_t pwm);
  void right    (uint8_t pwm);
  void turnLeft (uint8_t pwm);
  void turnRight(uint8_t pwm);
private:
  void _setDir(bool lFwd, bool rFwd);
};