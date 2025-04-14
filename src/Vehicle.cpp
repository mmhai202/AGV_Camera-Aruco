#include "Config.h"
#include "Vehicle.h"

void Vehicle::begin() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);  // IN1: left dir, IN2: left PWM
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);  // IN3: right PWM, IN4: right dir
  ledcSetup(PWM_CH_LEFT , PWM_FREQ, PWM_RES);  // Setup PWM for left motor
  ledcSetup(PWM_CH_RIGHT, PWM_FREQ, PWM_RES);  // Setup PWM for right motor
  ledcAttachPin(IN2, PWM_CH_LEFT);             // Attach PWM to left motor
  ledcAttachPin(IN3, PWM_CH_RIGHT);            // Attach PWM to right motor
  stop();                                      // Stop motors at the beginning
}
void Vehicle::stop()                { _setDir(0,0); ledcWrite(PWM_CH_LEFT,0);       ledcWrite(PWM_CH_RIGHT,0);}
void Vehicle::forward  (uint8_t pwm){ _setDir(0,1); ledcWrite(PWM_CH_LEFT,pwm);     ledcWrite(PWM_CH_RIGHT,255-pwm);}
void Vehicle::back     (uint8_t pwm){ _setDir(1,0); ledcWrite(PWM_CH_LEFT,255-pwm); ledcWrite(PWM_CH_RIGHT,pwm);}
void Vehicle::left     (uint8_t pwm){ _setDir(1,1); ledcWrite(PWM_CH_LEFT,255-pwm); ledcWrite(PWM_CH_RIGHT,255-pwm);}
void Vehicle::right    (uint8_t pwm){ _setDir(0,0); ledcWrite(PWM_CH_LEFT,pwm);     ledcWrite(PWM_CH_RIGHT,pwm);}
void Vehicle::turnLeft (uint8_t pwm){ _setDir(1,1); ledcWrite(PWM_CH_LEFT,255-pwm); ledcWrite(PWM_CH_RIGHT,255-pwm); delay(2000);}
void Vehicle::turnRight(uint8_t pwm){ _setDir(0,0); ledcWrite(PWM_CH_LEFT,pwm);     ledcWrite(PWM_CH_RIGHT,pwm); delay(2000);}
void Vehicle::_setDir(bool lFwd, bool rFwd) {  // Set motor direction
  digitalWrite(IN1, lFwd);
  digitalWrite(IN4, rFwd);
}
