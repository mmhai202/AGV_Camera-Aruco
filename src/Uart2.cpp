#include "Uart2.h"

void Uart2::begin(HardwareSerial* port, uint32_t baud, int8_t rx, int8_t tx){
  _ser=port;
  _ser->begin(baud, SERIAL_8N1, rx, tx);
}
bool Uart2::available(){return _ser->available();}
Data Uart2::read(){
  String s = _ser->readStringUntil('\n');
  Data d;
  int c1 = s.indexOf(','), c2 = s.indexOf(',',c1+1), c3 = s.indexOf(',',c2+1);
  d.id = s.substring(0,c1).toInt();
  d.x  = s.substring(c1+1,c2).toInt();
  d.y  = s.substring(c2+1,c3).toInt();
  d.angle = s.substring(c3+1).toFloat();
  return d;
}