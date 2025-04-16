#pragma once

// BlynkHandler
#define BLYNK_TEMPLATE_ID   "TMPL6i0G0w7eM"
#define BLYNK_TEMPLATE_NAME "agv"
#define BLYNK_AUTH_TOKEN    "iqpd9uR8FqKjTXxOW5QeLO_43JlZymip"

// WiFi
constexpr char WIFI_SSID[] = "ABC"; // constexpr giúp xác định giá trị và hàm tại thời điểm biên dịch
constexpr char WIFI_PASS[] = "03072002";

// Vehicle
constexpr int IN1_L_PWM = 5;
constexpr int IN2_L_DIR = 18;
constexpr int IN3_R_PWM = 19;
constexpr int IN4_R_DIR = 21;
constexpr int PWM_CH_LEFT  = 0;
constexpr int PWM_CH_RIGHT = 1;
constexpr int PWM_FREQ     = 5000;
constexpr int PWM_RES      = 8;

// Encoder
constexpr int ENCODER_L = 26;
constexpr int ENCODER_R = 27;

// UART2 data
struct Data {
  int id;
  int x;
  int y;
  float angle;
};