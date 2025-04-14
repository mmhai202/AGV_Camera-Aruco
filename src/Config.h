#pragma once

// Blynk
#define BLYNK_TEMPLATE_ID   "TMPL6i0G0w7eM"
#define BLYNK_TEMPLATE_NAME "agv"
#define BLYNK_AUTH_TOKEN    "iqpd9uR8FqKjTXxOW5QeLO_43JlZymip"

// Wi‑Fi
constexpr char WIFI_SSID[] = "ABC"; // constexpr giúp xác định giá trị và hàm tại thời điểm biên dịch
constexpr char WIFI_PASS[] = "03072002";

// GPIO
constexpr int IN1 = 27;
constexpr int IN2 = 26;
constexpr int IN3 = 19;
constexpr int IN4 = 18;

// PWM
constexpr int PWM_CH_LEFT  = 0;
constexpr int PWM_CH_RIGHT = 1;
constexpr int PWM_FREQ     = 5000;
constexpr int PWM_RES      = 8;

// UART2 data
struct Data {
  int id;
  int x;
  int y;
  float angle;
};