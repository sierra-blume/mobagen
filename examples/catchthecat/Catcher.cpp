#include "Catcher.h"
#include "World.h"
#include <vector>

Point2D Catcher::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  if (path.empty()) {
    auto side = world->getWorldSideSize() / 2;
    for (;;) {
      Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
      auto cat = world->getCat();
      if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
    }
  }
  return path.front();
}
