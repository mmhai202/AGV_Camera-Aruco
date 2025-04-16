#include "Vehicle.h"
#include "Uart2.h"
#include "BlynkHandler.h"
#include "Encoder.h"
#include "AStar.h"

// Khai báo các đối tượng cần thiết
Vehicle       vehicle; // Quản lý xe
Uart2         uart2;   // Nhận dữ liệu từ raspberry pi camera
BlynkHandler  blynk;   // Điều khiển xe qua Blynk
Encoder       encoder; // Đo vị trí xe
AStar         astar;   // Thuật toán A*

void setup() {
  Serial.begin(115200);
  encoder.begin();
  uart2.begin(&Serial2);
  vehicle.begin(&encoder, &uart2);
  astar.begin();
  blynk.begin(&vehicle);
  std::vector<Node*> path = astar.findPath(astar.start, astar.goal);
  Serial.println("Path found:");
  for (Node* node : path) {
    Serial.print("Node ID: ");
    Serial.print(node->id);
    Serial.print(" - Position: ");
    Serial.print(node->x);
    Serial.print(", ");
    Serial.println(node->y);
  }
}

void loop() {
  blynk.run();
}
