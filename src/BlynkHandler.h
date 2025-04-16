#pragma once
#include "Vehicle.h"

class BlynkHandler {
public:
  void begin(Vehicle* v);
  void run();
  static Vehicle* vehicle;
};