#include "Config.h"
#include <BlynkSimpleEsp32.h>
#include "BlynkHandler.h"

Vehicle*  BlynkHandler::vehicle = nullptr;
void BlynkHandler::begin(Vehicle* v){ 
  printf("Connecting to Blynk...\n");
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  printf("Connected to Blynk!\n");
  BlynkHandler::vehicle = v;
}
void BlynkHandler::run() { Blynk.run();}
void BlynkHandler::write(int pin, int value) { Blynk.virtualWrite(pin, value);}
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
    BlynkHandler::vehicle->f10 = true;
  }
}

BLYNK_WRITE(V9){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->l90 = true;
  }
}

BLYNK_WRITE(V10){ 
  if(param.asInt()) {
    BlynkHandler::vehicle->r90 = true;
  }
}