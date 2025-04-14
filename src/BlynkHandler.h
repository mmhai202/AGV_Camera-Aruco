#pragma once
#include "Vehicle.h"

class BlynkHandler {
public:
  void begin();
  void set_vehicle(Vehicle* v);
  void run();
  static Vehicle* vehicle;
};