#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) { //add in a separation radius
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  for(Boid* b : neighborhood) {
    if (boid->getPosition().x == b->getPosition().x && boid->getPosition().y == b->getPosition().y) {
      continue;
    }
    Vector2f sepVec = {boid->getPosition().x - b->getPosition().x, boid->getPosition().y - b->getPosition().y};
    float dist = sepVec.getMagnitude();
    if (dist < desiredMinimalDistance && dist > 0.01f) {
      sepVec = sepVec / dist;
      float force = desiredMinimalDistance / dist;
      separatingForce = Vector2f(separatingForce.x + sepVec.x * force, separatingForce.y + sepVec.y * force);
    }
  }
  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
