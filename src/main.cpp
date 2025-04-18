#include "Vehicle.h"
#include "Uart2.h"
#include "BlynkHandler.h"
#include "Encoder.h"
#include "AStar.h"

// Khai báo các đối tượng cần thiết
Vehicle       v; // Quản lý xe
Uart2         uart2;   // Nhận dữ liệu từ raspberry pi camera
BlynkHandler  blynk;   // Điều khiển xe qua Blynk
Encoder       encoder; // Đo vị trí xe
AStar         astar;   // Thuật toán A*

void taskRunBlynk(void* pvParameters) {
  while (1) {
    blynk.run();
    vTaskDelay(pdMS_TO_TICKS(10));  // Delay 10ms
  }
}

void taskControl(void* pvParameters) {
  while (1) {
    bool qrAvailable = v.checkQRCode(); // Kiểm tra xem có mã QR không
    if (qrAvailable) {
      v.qrData = uart2.read();
      if (v.ctrlState == DONE_STEP || v.ctrlState == START) {
        v.stop();
        v.speed = 110;
        v.ctrlState = ALIGN_QR;
      } else if (v.ctrlState == ALIGN_QR) {
        v.processQRCode();
        if (v.errorPosQR < 10 && v.errorAngQR < 5) { // Nếu đã căn chỉnh xong mã QR
          v.stop();
          v.ctrlState = DONE_QR;
          if (v.stepIdx < v.steps.size()) {
            v.speed = 120;
            v.dir = v.steps[v.stepIdx].dir; // Cập nhật hướng xe
            v.stepIdx++; // Chuyển sang bước tiếp theo
          } else {
            v.ctrlState = STOP; // Nếu đã hoàn thành tất cả các bước
          }
        }
      } 
    }
    if (!qrAvailable && v.ctrlState == DONE_QR) {v.ctrlState = RUN_STEP;}
    if (v.ctrlState == RUN_STEP) {v.processSteps(); v.ctrlState = DONE_STEP;}
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

void setup() {
  Serial.begin(115200);
  encoder.begin();
  astar.begin();
  uart2.begin(&Serial2);
  v.begin(&encoder, &uart2, &astar);
  blynk.begin(&v);
  std::vector<Node*> path = astar.findPath(astar.start, astar.goal);
  for (Node* node : path) {Serial.print("->"); Serial.print(node->id);}
  Serial.println("\n");
  v.buildSteps(path);

  // Tạo các task FreeRTOS
  xTaskCreate(taskRunBlynk, "TaskRunBlynk", 10000, NULL, 1, NULL);
  xTaskCreate(taskControl, "TaskControl", 10000, NULL, 1, NULL);
}

void loop() {
  // Nothing to do here, all tasks are handled in FreeRTOS tasks
}
