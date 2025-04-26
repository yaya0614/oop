#pragma once
#include "../MapBackground.hpp"
#include "MGameObject.hpp"
#include "Util/Image.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class NewCharacter : public MGameObject {
public:
  int dir_out = 0;
  int offest; // 移到 protected，讓子類可讀寫

  glm::vec2 position;
  glm::vec2 velocity;
  // int offest = -4;

  glm::vec2 size = {30, 40};
  glm::vec2 remainder;
  NewCharacter(glm::vec2 startPos, int offest = -1); // 加上參數
  virtual ~NewCharacter() = default;

  virtual void MoveX(float amount,
                     const std::vector<MapBackground::Platform> &platforms);
  virtual void MoveY(float amount,
                     const std::vector<MapBackground::Platform> &platforms);
  virtual void Update(float deltaTime,
                      const std::vector<MapBackground::Platform> &platforms);

  virtual void OnCollideX() {}
  virtual void OnCollideY() {}

  bool IsCollidingWithPlatform(
      const MapBackground::Platform &platform); // 判斷是否與某個平台相交

protected:
  std::shared_ptr<MGameObject> boxImage;
  float collisionTimer = 0.0f;
  bool isColliding = false;
};
