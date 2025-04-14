#include "Config.h"
#include <BlynkSimpleEsp32.h>
#include "BlynkHandler.h"

Vehicle*  BlynkHandler::vehicle = nullptr;
void BlynkHandler::begin(){ 
  printf("Connecting to Blynk...\n");
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  printf("Connected to Blynk!\n");
}
void BlynkHandler::set_vehicle(Vehicle* v){ 
  BlynkHandler::vehicle = v;
  BlynkHandler::vehicle->speed = 120; // Default speed
}
void BlynkHandler::run() { Blynk.run();}
BLYNK_WRITE(V0){ param.asInt()? BlynkHandler::vehicle->forward(BlynkHandler::vehicle->speed):BlynkHandler::vehicle->stop();}
BLYNK_WRITE(V1){ param.asInt()? BlynkHandler::vehicle->back   (BlynkHandler::vehicle->speed):BlynkHandler::vehicle->stop();}
BLYNK_WRITE(V2){ param.asInt()? BlynkHandler::vehicle->left   (BlynkHandler::vehicle->speed):BlynkHandler::vehicle->stop();}
BLYNK_WRITE(V3){ param.asInt()? BlynkHandler::vehicle->right  (BlynkHandler::vehicle->speed):BlynkHandler::vehicle->stop();}
BLYNK_WRITE(V4){ BlynkHandler::vehicle->speed = map(param.asInt(),1,10,1,10)*10+100; printf("Speed: %d\n", BlynkHandler::vehicle->speed);}