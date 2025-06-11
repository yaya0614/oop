#ifndef COLLIDERS_HPP
#define COLLIDERS_HPP

#include <glm/glm.hpp>

class Colliders {
public:
  glm::vec2 position;
  glm::vec2 size;

  Colliders(glm::vec2 pos, glm::vec2 sz) : position(pos), size(sz) {}

  virtual bool IsCollidingWith(const Colliders &other) const {
    float leftA = position.x - size.x / 2;
    float rightA = position.x + size.x / 2;
    float topA = position.y + size.y / 2;
    float bottomA = position.y - size.y / 2;

    float leftB = other.position.x - other.size.x / 2;
    float rightB = other.position.x + other.size.x / 2;
    float topB = other.position.y + other.size.y / 2;
    float bottomB = other.position.y - other.size.y / 2;

    return !(leftA > rightB || rightA < leftB || bottomA > topB ||
             topA < bottomB);
  }
};

#endif
