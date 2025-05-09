#include "actors/NewCharacter.hpp"
#include "Util/Animation.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include <cmath>
#include <glm/fwd.hpp>
#include <memory>
#include <string>

NewCharacter::NewCharacter(glm::vec2 startPos, std::string tag, int offest)
    : MGameObject(), Colliders(startPos, size), position(startPos),
      velocity(0.0f), remainder(0.0f), offest(offest) {
  boxImage = std::make_shared<MGameObject>();
  boxImage->SetDrawable(
      std::make_shared<Util::Image>(GA_RESOURCE_DIR "/Test/Rectangle 113.png"));
  boxImage->m_Transform.scale = size;
  boxImage->SetZIndex(100);
  boxImage->SetPosition({position.x, position.y + offest});
  this->tag = tag;
  if (tag == "fire") {
    animation_walk = std::make_shared<Util::Animation>(FireBoyAnimationPaths,
                                                       true, 80, true, 80);
  } else if (tag == "water") {
    animation_walk = std::make_shared<Util::Animation>(WaterGirlAnimationPaths,
                                                       true, 50, true, 50);
  }
}

bool IsCollidingWith(const MGameObject &other);

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

void NewCharacter::MoveX(float amount,
                         const std::vector<MapBackground::Platform> &platforms,
                         std::string tag) {
  std::string s = (tag == "fire") ? "boy" : "girl";

  remainder.x += amount;
  int move = std::round(remainder.x);
  remainder.x -= move;
  int dir = (move > 0) ? 1 : -1;
  dir_out = (move > 0) ? 1 : -1;
  if (move > 0) {
    dir_out = 1;
    SetDrawable(animation_walk);
    m_Transform.scale = glm::vec2{0.34, 0.34};

  } else if (move == 0) {
    dir_out = 0;
    m_Drawable = std::make_shared<Util::Image>(GA_RESOURCE_DIR "/" + tag + "/" +
                                               s + "_1.png");
  } else {
    dir_out = -1;
    SetDrawable(animation_walk);
    m_Transform.scale = glm::vec2{-0.34, 0.34};
  }

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

bool NewCharacter::IsCollidingWith(const MGameObject &other) {
  glm::vec2 pos1 = GetPosition();
  glm::vec2 pos2 = other.GetPosition();

  float distance = glm::distance(pos1, pos2);
  return distance < 40.0f;
};

std::string NewCharacter::GetStatus() { return status; };

void NewCharacter::Update(
    float deltaTime, const std::vector<MapBackground::Platform> &platforms) {
  velocity.y += 0.3f; // gravity
  MoveX(velocity.x * deltaTime, platforms, tag);
  MoveY(velocity.y * deltaTime, platforms);
}
