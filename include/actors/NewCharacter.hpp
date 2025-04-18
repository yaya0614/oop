#pragma once
#include "../MapBackground.hpp"
#include "MGameObject.hpp"
#include "Util/Image.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class NewCharacter : public MGameObject {
public:
  glm::vec2 position;
  glm::vec2 velocity;
  int offest = -4;

  glm::vec2 size = {30, 50};
  glm::vec2 remainder;

  NewCharacter(glm::vec2 startPos)
      : position(startPos), velocity(0.0f), remainder(0.0f) {
    boxImage = std::make_shared<MGameObject>();
    boxImage->SetDrawable(std::make_shared<Util::Image>(
        GA_RESOURCE_DIR "/Test/Rectangle 113.png"));
    boxImage->m_Transform.scale = size;
    boxImage->SetZIndex(100);
    boxImage->SetPosition({position.x, position.y});
  }
  virtual ~NewCharacter() = default;

  virtual void MoveX(float amount,
                     const std::vector<MapBackground::Platform> &platforms);
  virtual void MoveY(float amount,
                     const std::vector<MapBackground::Platform> &platforms);
  virtual void Update(float deltaTime,
                      const std::vector<MapBackground::Platform> &platforms);
  virtual void OnCollideX() {}
  virtual void OnCollideY() {}

  // 判斷是否與某個平台相交
  bool IsCollidingWithPlatform(const MapBackground::Platform &platform);

protected:
  // NewFireBoy.hpp class 內新增成員：
  std::shared_ptr<MGameObject> boxImage;
  float collisionTimer = 0.0f;
  bool isColliding = false;
};
