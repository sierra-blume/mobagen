//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) { return 0; }

/*
bool topLeft(World &world, Point2D point) {
  if (point.y % 2 == 0)
    return world.Get({point.x-1, point.y-1});
  else
    return world.Get({point.x, point.y-1});
}*/