#include "Config.h"
#include "Vehicle.h"

void Vehicle::begin(Encoder* encoder, Uart2* _uart2) {
  _encoder = encoder;
  _uart2 = _uart2;
  pinMode(IN1_L_PWM, OUTPUT); pinMode(IN2_L_DIR, OUTPUT);
  pinMode(IN3_R_PWM, OUTPUT); pinMode(IN4_R_DIR, OUTPUT);
  ledcSetup(PWM_CH_LEFT , PWM_FREQ, PWM_RES);  // Setup PWM for left motor
  ledcSetup(PWM_CH_RIGHT, PWM_FREQ, PWM_RES);  // Setup PWM for right motor
  ledcAttachPin(IN1_L_PWM, PWM_CH_LEFT);       // Attach PWM to left motor
  ledcAttachPin(IN3_R_PWM, PWM_CH_RIGHT);      // Attach PWM to right motor
  stop();                                      // Stop motors at the beginning
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
