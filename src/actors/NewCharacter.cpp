#include "actors/NewCharacter.hpp"
#include "Util/Logger.hpp"
#include <cmath>
#include <glm/fwd.hpp>

bool NewCharacter::IsCollidingWithPlatform(
    const MapBackground::Platform &platform) {

  glm::vec2 tag = {position.x, position.y + offest};
  float left = tag.x - size.x / 2;
  float right = tag.x + size.x / 2;
  float top = tag.y + size.y / 2;
  float bottom = tag.y - size.y / 2;
  // LOG_DEBUG(bottom);
  const int epsilon = 1;

  return (right >= platform.x1 - epsilon && left <= platform.x2 + epsilon &&
          bottom <= platform.y_high + epsilon &&
          top >= platform.y_low - epsilon);
}

void NewCharacter::MoveX(
    float amount, const std::vector<MapBackground::Platform> &platforms) {
  remainder.x += amount;
  int move = std::round(remainder.x);
  remainder.x -= move;
  int dir = (move > 0) ? 1 : -1;

  while (move != 0) {
    position.x += dir;

    for (const auto &p : platforms) {
      if (IsCollidingWithPlatform(p)) {
        position.x -= dir * 2;
        remainder.x = 0;
        OnCollideX();
        return;
      }
    }
    move -= dir;
  }
}

void NewCharacter::MoveY(
    float amount, const std::vector<MapBackground::Platform> &platforms) {
  remainder.y += amount;
  int move = std::round(remainder.y);
  remainder.y -= move;
  int dir = (move > 0) ? 1 : -1;

  while (move != 0) {
    position.y += dir;

    glm::vec2 tag = {position.x, position.y + offest};
    float top = tag.y + size.y / 2;
    float bottom = tag.y - size.y / 2;

    for (const auto &p : platforms) {
      if (IsCollidingWithPlatform(p)) {
        if (dir > 0 && bottom <= p.y_high && bottom >= p.y_high - 5.0f) {
          position.y = p.y_high - size.y / 2 - offest;
          remainder.y = 0;
          return;
        } else if (dir < 0 && top >= p.y_low && top <= p.y_low + 5.0f) {
          position.y = p.y_low - size.y / 2 - offest;
          remainder.y = 0;
          return;
        } else {
          position.y -= dir * 2;
          remainder.y = 0;
          OnCollideY();
          return;
        }
      }
    }
    move -= dir;
  }
}

void NewCharacter::Update(
    float deltaTime, const std::vector<MapBackground::Platform> &platforms) {
  velocity.y += 0.3f; // gravity
  MoveX(velocity.x * deltaTime, platforms);
  MoveY(velocity.y * deltaTime, platforms);
}
