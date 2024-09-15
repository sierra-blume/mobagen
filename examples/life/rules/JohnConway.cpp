#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

  for(int y = 0; y < world.SideSize(); y++) {
    for (int x = 0; x < world.SideSize(); x++) {
      Point2D p = Point2D(x, y);
      if (world.Get(p)) {
        if (CountNeighbors(world, p) < 2 || CountNeighbors(world, p) > 3)
          world.SetNext(p, false);
        else
          world.SetNext(p, true);
      }
      else {
        if (CountNeighbors(world, p) == 3)
          world.SetNext(p, true);
      }
    }
  }
  world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int neighbors = 0;

  for (int y = -1; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      Point2D p = Point2D((point.x + x) % world.SideSize(), (point.y + y) % world.SideSize());
      if(p != point && world.Get(p))
        neighbors++;
    }
  }
  return neighbors;
}