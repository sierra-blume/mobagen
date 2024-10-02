#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  if (!stack.empty()) {
    Point2D current = stack.back();
    std::vector<Point2D> neighbors = getVisitables(w, current);
    visited[current.x][current.y] = true;
    if(!neighbors.empty()) {
      w->SetNodeColor(stack.back(), Color::Azure);
      Point2D nextNeighbor = neighbors.front();
      if(neighbors.size() != 1) {
        Random rnd;
        nextNeighbor = neighbors[rnd.Range(0, neighbors.size() - 1)];
      }
      if(current.Up() == nextNeighbor) {
        w->SetSouth(nextNeighbor, false);
        w->SetNorth(current, false);
      }
      if(current.Down() == nextNeighbor) {
        w->SetNorth(nextNeighbor, false);
        w->SetSouth(current, false);
      }
      if(current.Left() == nextNeighbor) {
        w->SetEast(nextNeighbor, false);
        w->SetWest(current, false);
      }
      if(current.Right() == nextNeighbor) {
        w->SetWest(nextNeighbor, false);
        w->SetEast(current, false);
      }
      stack.push_back(nextNeighbor);
      return true;
    }
    else {
      w->SetNodeColor(stack.back(), Color::Black);
      stack.pop_back();
      return true;
    }
  }
  else {
    stack.push_back(randomStartPoint(w));
  }
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this
  if(w->isValidPosition(p.Up())) {
    if(!visited[p.Up().x][p.Up().y]) visitables.push_back(p.Up());
  }
  if(w->isValidPosition(p.Down())) {
    if(!visited[p.Down().x][p.Down().y]) visitables.push_back(p.Down());
  }
  if(w->isValidPosition(p.Left())) {
    if(!visited[p.Left().x][p.Left().y]) visitables.push_back(p.Left());
  }
  if(w->isValidPosition(p.Right())) {
    if(!visited[p.Right().x][p.Right().y]) visitables.push_back(p.Right());
  }

  return visitables;
}
