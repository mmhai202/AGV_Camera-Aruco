#include "Encoder.h"

volatile int Encoder::encoderL = 0;
volatile int Encoder::encoderR = 0;
bool Encoder::isCounting = false;
void Encoder::begin() {
  pinMode(ENCODER_L, INPUT_PULLUP);
  pinMode(ENCODER_R, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_L), isr1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R), isr2, RISING);}
void Encoder::start() {
  isCounting = true;
  reset();}
void Encoder::stop() {
  isCounting = false;}
void Encoder::reset() {encoderL = 0; encoderR = 0;}
int Encoder::getL() {return encoderL;}
int Encoder::getR() {return encoderR;}
void IRAM_ATTR Encoder::isr1() {if(isCounting) encoderL++;}
void IRAM_ATTR Encoder::isr2() {if(isCounting) encoderR++;}