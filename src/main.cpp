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
std::vector<Node*> grid;  // Khai báo grid là vector chứa các node ArUco

void setup() {
  Serial.begin(115200);
  encoder.begin();
  uart2.begin(&Serial2);
  vehicle.begin(&encoder, &uart2);
  blynk.begin(&vehicle);

  // Tạo danh sách các node ArUco (ID 0 đến 11 với vị trí x, y)
  for (int i = 0; i < 12; i++) {
    Node* node = new Node();
    node->id = i;
    node->x = i % 4;  // Xác định tọa độ x
    node->y = i / 4;  // Xác định tọa độ y
    node->gCost = INT_MAX;
    node->hCost = 0;
    node->parent = nullptr;
    grid.push_back(node);
  }
}

bool start_plan = true;
// Tìm đường đi từ node bắt đầu (ID 0) đến node kết thúc (ID 11) sử dụng A*
AStar aStar(grid);
Node* start = grid[0];  // ArUco ID 0
Node* goal = grid[11];   // ArUco ID 11
std::vector<Node*> path = aStar.findPath(start, goal);

void loop() {
  blynk.run();
}
