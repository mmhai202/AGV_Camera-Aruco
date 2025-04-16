#include "Config.h"
#include <BlynkSimpleEsp32.h>
#include "BlynkHandler.h"

Vehicle*  BlynkHandler::vehicle = nullptr;
void BlynkHandler::begin(Vehicle* v){ 
  printf("Connecting to Blynk...\n");
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  printf("Connected to Blynk!\n");
  BlynkHandler::vehicle = v;
  BlynkHandler::vehicle->speed = 120; // Default speed
  BlynkHandler::vehicle->forward_10cm = false;
  BlynkHandler::vehicle->turnleft_90deg = false;
  BlynkHandler::vehicle->turnright_90deg = false;
  printf("Default Speed: %d\n", BlynkHandler::vehicle->speed);
}
void BlynkHandler::run() { Blynk.run();}
BLYNK_WRITE(V0){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->left(BlynkHandler::vehicle->speed);
    BlynkHandler::vehicle->right(BlynkHandler::vehicle->speed);
  } else {
    BlynkHandler::vehicle->stop();
  }
}

BLYNK_WRITE(V1) {
  if(param.asInt()) {
    BlynkHandler::vehicle->left(-(BlynkHandler::vehicle->speed));
    BlynkHandler::vehicle->right(-(BlynkHandler::vehicle->speed));
  } else {
    BlynkHandler::vehicle->stop();
  }
}

BLYNK_WRITE(V2){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->left(-(BlynkHandler::vehicle->speed));
    BlynkHandler::vehicle->right(BlynkHandler::vehicle->speed);
  } else {
    BlynkHandler::vehicle->stop();
  }
}

BLYNK_WRITE(V3){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->left(BlynkHandler::vehicle->speed);
    BlynkHandler::vehicle->right(-(BlynkHandler::vehicle->speed));
  } else {
    BlynkHandler::vehicle->stop();
  }
}

BLYNK_WRITE(V4){ BlynkHandler::vehicle->speed = map(param.asInt(),1,10,1,10)*10+100; 
                 printf("Speed: %d\n", BlynkHandler::vehicle->speed);}

BLYNK_WRITE(V8){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->forward_10cm = true;
  } else {
    BlynkHandler::vehicle->forward_10cm = false;
  }
}

BLYNK_WRITE(V9){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->turnleft_90deg = true;
  } else {
    BlynkHandler::vehicle->turnleft_90deg = false;
  }
}

BLYNK_WRITE(V10){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->turnright_90deg = true;
  } else {
    BlynkHandler::vehicle->turnright_90deg = false;
  }
}