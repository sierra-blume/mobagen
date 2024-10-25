#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D current, unordered_set<Point2D> frontierSet, unordered_map<Point2D, bool> visited) {
  std::vector<Point2D> allNeighbors = w->neighbors(current);
  std::vector<Point2D> visitableNeighbors;
  for (auto neighbor : allNeighbors) {
    if (w->catcherCanMoveToPosition(neighbor) && !w->getContent(neighbor) && !frontierSet.contains(neighbor) && !visited.contains(neighbor)) {
      visitableNeighbors.push_back(neighbor);
    }
  }
  return visitableNeighbors;
}

bool operator<(const Point2D& left, const Point2D& right) {return (left.x < right.x) || (left.x == right.x && left.y < right.y);}

bool operator>(const Point2D& left, const Point2D& right) {return (left.x > right.x) || (left.x == right.x && left.y > right.y);}

int heuristics (World* w, Point2D point) {
  int halfWidth = w->getWorldSideSize() / 2;

  if (abs(point.x) < abs(point.y))
    return halfWidth - abs(point.y);

  return halfWidth - abs(point.x);
}

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<std::pair<int, Point2D>, std::vector<std::pair<int, Point2D>>, std::greater<std::pair<int, Point2D>>> frontier; // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  unordered_map<Point2D, int> costSoFar;

  // bootstrap state
  auto catPos = w->getCat();
  frontier.emplace(0, catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontierSet.empty()) {
    // get the current from frontier
    auto current = frontier.top().second;
    // remove the current from frontierset
    frontier.pop();
    frontierSet.erase(current);
    // mark current as visited
    visited[current] = true;

    if (w->catWinsOnSpace(current)) {
      //put return statement
      vector<Point2D> path;
      Point2D pathCurrent = current;
      while (pathCurrent != catPos) {
        path.push_back(pathCurrent);
        pathCurrent = cameFrom[pathCurrent];
      }
      return path;
    }

    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, current, frontierSet, visited);

    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop

    int cost = costSoFar[current] + 1;
    for (int i = 0; i < visitableNeighbors.size(); i++) {
      if(costSoFar.find(visitableNeighbors[i]) == costSoFar.end() || costSoFar[visitableNeighbors[i]] > cost) {
        costSoFar[visitableNeighbors[i]] = cost + 1;
        int priority = cost + heuristics(w, visitableNeighbors[i]);
        frontier.emplace(priority, visitableNeighbors[i]);
        frontierSet.insert(visitableNeighbors[i]);
        cameFrom[visitableNeighbors[i]] = current;
      }
    }

    cout << frontier.size() << "  " << frontierSet.size() << endl;
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}