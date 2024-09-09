#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f(0, 0);

  // hint: iterate over the neighborhood
  Vector2f localTotal = Vector2f(0, 0);

  if (neighborhood.size() == 0) {return cohesionForce;}

  for(Boid *b : neighborhood) {
    if(b->getPosition().x == boid->getPosition().x && b->getPosition().y == boid->getPosition().y) {
      continue;
    }
    localTotal += b->getPosition();
  }
  // find center of mass
  Vector2f centerMass = Vector2f(localTotal.x / neighborhood.size(), localTotal.y / neighborhood.size());

  Vector2f dist = centerMass - boid->getPosition();
  cohesionForce = dist.normalized();

  return cohesionForce;
}