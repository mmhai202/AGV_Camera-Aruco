// AStar.cpp
#include "AStar.h"
#include <algorithm>

AStar::AStar(std::vector<Node*>& grid) {
  this->grid = grid;
}

int AStar::heuristic(Node* current, Node* goal) {
  return abs(current->x - goal->x) + abs(current->y - goal->y);  // Khoảng cách Manhattan
}

std::vector<Node*> AStar::findPath(Node* start, Node* goal) {
  std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
  std::map<int, bool> closedList;

  start->gCost = 0;
  start->hCost = heuristic(start, goal);
  openList.push(start);

  while (!openList.empty()) {
    Node* current = openList.top();
    openList.pop();

    if (current == goal) {
      std::vector<Node*> path;
      while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
      }
      std::reverse(path.begin(), path.end());
      return path;
    }

    closedList[current->id] = true;

    // Duyệt qua các node lân cận (lên, xuống, trái, phải)
    std::vector<std::pair<int, int>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // Các hướng di chuyển
    for (auto& dir : neighbors) {
      int newX = current->x + dir.first;
      int newY = current->y + dir.second;

      // Kiểm tra nếu node mới hợp lệ (trong phạm vi bản đồ và không phải vật cản)
      if (newX >= 0 && newX < 4 && newY >= 0 && newY < 3) {
        Node* neighbor = grid[newX + newY * 4];  // Lấy node lân cận

        if (neighbor->isBlocked || closedList[neighbor->id]) continue;  // Nếu node là vật cản hoặc đã thăm, bỏ qua

        int tentativeGCost = current->gCost + 1;  // Chi phí tạm thời từ node hiện tại đến neighbor
        if (tentativeGCost < neighbor->gCost || !closedList[neighbor->id]) {
          neighbor->parent = current;
          neighbor->gCost = tentativeGCost;
          neighbor->hCost = heuristic(neighbor, goal);
          openList.push(neighbor);  // Thêm neighbor vào openList
        }
      }
    }
  }

  return {};  // Không tìm thấy đường đi
}
