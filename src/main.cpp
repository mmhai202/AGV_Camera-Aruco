#include "Vehicle.h"
#include "Uart2.h"
#include "BlynkHandler.h"

Vehicle       vehicle;
Uart2         uart2;
BlynkHandler  blynk;
Data          data;

volatile int encoderL = 0;
volatile int encoderR = 0;
void IRAM_ATTR isr1() {encoderL++;}
void IRAM_ATTR isr2() {encoderR++;}

void enableEncoder() {
  attachInterrupt(digitalPinToInterrupt(25), isr1, RISING);
  attachInterrupt(digitalPinToInterrupt(24), isr2, RISING);
}

void disableEncoder() {
  detachInterrupt(digitalPinToInterrupt(25));
  detachInterrupt(digitalPinToInterrupt(24));
  encoderL = 0;
  encoderR = 0;
}

void setup(){
  Serial.begin(115200);
  uart2.begin(&Serial2);
  vehicle.begin();
  blynk.begin();
  blynk.set_vehicle(&vehicle);
  pinMode(25, INPUT);
  pinMode(24, INPUT);
}

void loop(){
  blynk.run();
}
