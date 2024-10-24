#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>

class World;

struct Cost {

};

struct ANode {
  Point2D pos;
  int cost;
  Cost estCost;
};

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> getVisitableNeighbors(World* w, Point2D current, std::unordered_set<Point2D> frontierSet, std::unordered_map<Point2D, bool> visited);

  std::vector<Point2D> generatePath(World* w);
};

#endif  // AGENT_H
