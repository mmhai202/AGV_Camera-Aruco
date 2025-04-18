#pragma once
#include <Arduino.h>
#include "Encoder.h"
#include "Uart2.h"
#include "AStar.h"

// Các loại hành động
enum Action {IDLE, FWD, BACK, LEFT, RIGHT};
enum Direction {POS_X, NEG_X, POS_Y, NEG_Y};
enum CtrlState {START, RUN_STEP, DONE_STEP, ALIGN_QR , DONE_QR, STOP};

// Cấu trúc bước di chuyển
struct Step {
  int id;
  Action act;
  Direction dir;
};

class Vehicle {
public:
  void begin(Encoder* encoder, Uart2* uart2, AStar* astar); // Khởi tạo xe
  void stop();
  void left(int16_t pwm);
  void right(int16_t pwm);
  void buildSteps(const std::vector<Node*>& path);
  void startStep(const Step& s);
  void processSteps();
  bool checkQRCode();
  void processQRCode();
  int16_t speed = 120;
  Direction dir = POS_Y;
  CtrlState ctrlState = START;
  size_t stepIdx = 0;
  std::vector<Step> steps;
  Data qrData;
  int errorPosQR;
  int errorAngQR;
private:
  Encoder* _encoder;
  Uart2* _uart2;
  AStar* _astar;
};