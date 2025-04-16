// AStar.h
#pragma once
#include <vector>
#include <map>
#include <queue>

struct Node {
  int id;
  int x, y;
  int gCost;
  int hCost;
  int fCost() { return gCost + hCost; }
  Node* parent;
  bool isBlocked = false;  // Đánh dấu node này có vật cản không
};

// Cấu trúc so sánh để sắp xếp priority_queue
struct CompareNode {
  bool operator()(Node* a, Node* b) {
    return a->fCost() > b->fCost();  // So sánh fCost của các node
  }
};

class AStar {
public:
  AStar(std::vector<Node*>& grid);
  std::vector<Node*> findPath(Node* start, Node* goal);

private:
  int heuristic(Node* current, Node* goal);
  std::vector<Node*> grid;
};
