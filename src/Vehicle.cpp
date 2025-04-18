#include "Config.h"
#include "Vehicle.h"

void Vehicle::begin(Encoder* encoder, Uart2* uart2, AStar* astar) {
  _encoder = encoder;
  _uart2 = uart2;
  _astar = astar;
  pinMode(IN1_L_PWM, OUTPUT); pinMode(IN2_L_DIR, OUTPUT);
  pinMode(IN3_R_PWM, OUTPUT); pinMode(IN4_R_DIR, OUTPUT);
  ledcSetup(PWM_CH_LEFT , PWM_FREQ, PWM_RES);  // Setup PWM for left motor
  ledcSetup(PWM_CH_RIGHT, PWM_FREQ, PWM_RES);  // Setup PWM for right motor
  ledcAttachPin(IN1_L_PWM, PWM_CH_LEFT);       // Attach PWM to left motor
  ledcAttachPin(IN3_R_PWM, PWM_CH_RIGHT);      // Attach PWM to right motor
  stop();
}
void Vehicle::stop() { 
  digitalWrite(IN2_L_DIR, LOW);
  digitalWrite(IN4_R_DIR, LOW);
  ledcWrite(PWM_CH_LEFT,0);
  ledcWrite(PWM_CH_RIGHT,0);
}

void Vehicle::left(int16_t pwm) {
  if(pwm > 0) {
    digitalWrite(IN2_L_DIR, HIGH); 
    ledcWrite(PWM_CH_LEFT, 255-pwm);
  } else {
    digitalWrite(IN2_L_DIR, LOW); 
    ledcWrite(PWM_CH_LEFT, -pwm);
  }
}

void Vehicle::right(int16_t pwm) { 
  if(pwm >= 0) {
    digitalWrite(IN4_R_DIR, HIGH); 
    ledcWrite(PWM_CH_RIGHT, 255-pwm);
  } else {
    digitalWrite(IN4_R_DIR, LOW); 
    ledcWrite(PWM_CH_RIGHT, -pwm);
  }
}

void Vehicle::buildSteps(const std::vector<Node*>& path) {
  steps.clear();
  stepIdx = 0;
  steps.push_back({path[0]->id ,Action::IDLE, dir});
  Direction path_dir = dir;
  for (size_t i = 1; i < path.size(); i++) {
    int dx = path[i]->x - path[i-1]->x;
    int dy = path[i]->y - path[i-1]->y;
    
    if (dy ==  1 && path_dir == POS_Y) {steps.push_back({path[i]->id, Action::FWD, Direction::POS_Y}); path_dir = POS_Y;}
    if (dy == -1 && path_dir == POS_Y) {steps.push_back({path[i]->id, Action::BACK, Direction::NEG_Y}); path_dir = NEG_Y;}
    if (dx ==  1 && path_dir == POS_Y) {steps.push_back({path[i]->id, Action::LEFT, Direction::POS_X}); path_dir = POS_X;}
    if (dx == -1 && path_dir == POS_Y) {steps.push_back({path[i]->id, Action::RIGHT, Direction::NEG_X}); path_dir = NEG_X;}

    if (dy ==  1 && path_dir == NEG_Y) {steps.push_back({path[i]->id, Action::BACK, Direction::NEG_Y}); path_dir = NEG_Y;}
    if (dy == -1 && path_dir == NEG_Y) {steps.push_back({path[i]->id, Action::FWD, Direction::POS_Y}); path_dir = POS_Y;} 
    if (dx ==  1 && path_dir == NEG_Y) {steps.push_back({path[i]->id, Action::RIGHT, Direction::POS_X}); path_dir = POS_X;}
    if (dx == -1 && path_dir == NEG_Y) {steps.push_back({path[i]->id, Action::LEFT, Direction::NEG_X}); path_dir = NEG_X;}

    if(dy ==  1 && path_dir == POS_X) {steps.push_back({path[i]->id, Action::RIGHT, Direction::POS_Y}); path_dir = POS_Y;}
    if(dy == -1 && path_dir == POS_X) {steps.push_back({path[i]->id, Action::LEFT, Direction::NEG_Y}); path_dir = NEG_Y;}
    if(dx ==  1 && path_dir == POS_X) {steps.push_back({path[i]->id, Action::FWD, Direction::POS_X}); path_dir = POS_X;}
    if(dx == -1 && path_dir == POS_X) {steps.push_back({path[i]->id, Action::BACK, Direction::NEG_X}); path_dir = NEG_X;}

    if(dy ==  1 && path_dir == NEG_X) {steps.push_back({path[i]->id, Action::LEFT, Direction::POS_Y}); path_dir = POS_Y;}
    if(dy == -1 && path_dir == NEG_X) {steps.push_back({path[i]->id, Action::RIGHT, Direction::NEG_Y}); path_dir = NEG_Y;}
    if(dx ==  1 && path_dir == NEG_X) {steps.push_back({path[i]->id, Action::BACK, Direction::POS_X}); path_dir = POS_X;}
    if(dx == -1 && path_dir == NEG_X) {steps.push_back({path[i]->id, Action::FWD, Direction::NEG_X}); path_dir = NEG_X;}
  }
}

void Vehicle::startStep(const Step& s) {
  // Bắt đầu thực hiện bước
  switch (s.act) {
    case Action::FWD:
      left(speed);
      right(speed);
      break;
    case Action::BACK:
      left(-speed);
      right(-speed);
      break;
    case Action::LEFT:
      left(-speed);
      right(speed);
      break;
    case Action::RIGHT:
      left(speed);
      right(-speed);
      break;
    default:
      break;
  }
}

void Vehicle::processSteps() {
  startStep(steps[stepIdx]);
}

bool Vehicle::checkQRCode() {
  return _uart2->available();
}

void Vehicle::processQRCode() {
  int targetPosition;
  int targetAngle;
  if (steps[stepIdx].dir == POS_X) {
    targetPosition = qrData.y;
    targetAngle = -90.0;
  } else if (steps[stepIdx].dir == NEG_X) {
    targetPosition = qrData.y;
    targetAngle = 90.0;
  } else if (steps[stepIdx].dir == POS_Y) {
    targetPosition = qrData.x;
    targetAngle = 0.0;
  } else if (steps[stepIdx].dir == NEG_Y) {
    targetPosition = qrData.x;
    targetAngle = 180.0;
  }
  errorPosQR = targetPosition - 320;  // Sai số vị trí với mã
  errorAngQR = targetAngle - qrData.angle;  // Sai số góc với mã

  // Căn xe vào giữa mã QR
  //
}