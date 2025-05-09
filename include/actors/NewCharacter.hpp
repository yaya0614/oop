#pragma once
#include "../MapBackground.hpp"
#include "MGameObject.hpp"
#include "Util/Animation.hpp"
#include "Util/Image.hpp"
#include "collider/Colliders.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

class NewCharacter : public MGameObject, public Colliders {
public:
  int dir_out = 0;
  int offest;
  std::string tag;

  glm::vec2 position;
  glm::vec2 velocity;
  void Animation();
  glm::vec2 size = {30, 40};
  glm::vec2 remainder;
  NewCharacter(glm::vec2 startPos, std::string tag,
               int offest = -1); // 加上參數
  virtual ~NewCharacter() = default;

  // 加入人物的tag，以改變跑步時候的狀態
  void PlayAnimation(std::string tag, std::string s);
  virtual void MoveX(float amount,
                     const std::vector<MapBackground::Platform> &platforms,
                     std::string tag);
  virtual void MoveY(float amount,
                     const std::vector<MapBackground::Platform> &platforms);
  virtual void Update(float deltaTime,
                      const std::vector<MapBackground::Platform> &platforms);

  virtual void OnCollideX() {}
  virtual void OnCollideY() {}

  bool IsCollidingWith(const MGameObject &other);
  bool IsCollidingWithPlatform(
      const MapBackground::Platform &platform); // 判斷是否與某個平台相交
  virtual void ChangeStatus(std::string status){};
  std::string GetStatus();

protected:
  std::string status = "Alive";
  bool isJumping = false;
  float jumpingBuffer = 0.0f;
  const float gravity = -300.0f;
  const float jumpSpeed = 200.0f;
  const float targethigh = 9;
  bool isOnElevator = true;
  bool isColliding = false;
  bool onRock = false;

  std::shared_ptr<MGameObject> boxImage;
  float collisionTimer = 0.0f;
  std::shared_ptr<Util::Animation> animation_walk;
  const std::vector<std::string> FireBoyAnimationPaths = {
      GA_RESOURCE_DIR "/fire/boy_2.png",
      GA_RESOURCE_DIR "/fire/boy_3.png",
      GA_RESOURCE_DIR "/fire/boy_4.png",
      GA_RESOURCE_DIR "/fire/boy_5.png",
  };
  const std::vector<std::string> WaterGirlAnimationPaths = {
      GA_RESOURCE_DIR "/water/girl_3.png", GA_RESOURCE_DIR "/water/girl_4.png",
      GA_RESOURCE_DIR "/water/girl_5.png", GA_RESOURCE_DIR "/water/girl_6.png",
      GA_RESOURCE_DIR "/water/girl_7.png", GA_RESOURCE_DIR "/water/girl_8.png",
      GA_RESOURCE_DIR "/water/girl_9.png",
  };
};
