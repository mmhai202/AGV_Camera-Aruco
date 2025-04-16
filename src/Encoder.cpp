#include "Encoder.h"

volatile int Encoder::encoderL = 0;
volatile int Encoder::encoderR = 0;
void Encoder::begin() {
  pinMode(ENCODER_L, INPUT_PULLUP);
  pinMode(ENCODER_R, INPUT_PULLUP);}
void Encoder::start() {
  attachInterrupt(digitalPinToInterrupt(ENCODER_L), isr1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_R), isr2, RISING);
  reset();}
void Encoder::stop() {
  detachInterrupt(digitalPinToInterrupt(ENCODER_L));
  detachInterrupt(digitalPinToInterrupt(ENCODER_R));
  reset();}
void Encoder::reset() {encoderL = 0; encoderR = 0;}
int Encoder::getL() {return encoderL;}
int Encoder::getR() {return encoderR;}
void IRAM_ATTR Encoder::isr1() {encoderL++;}
void IRAM_ATTR Encoder::isr2() {encoderR++;}