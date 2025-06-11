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
class NewDoor;
class NewPool;
class NewBridge;
class NewElevator;
class NewRock;

class NewCharacter : public MGameObject, public Colliders {
public:
  int dir_out = 0;
  int offest;
  std::string tag;

  glm::vec2 position;
  glm::vec2 velocity;

  glm::vec2 size = {30, 40};
  glm::vec2 remainder;

  NewCharacter(glm::vec2 startPos, std::string tag, int offest = -1);
  virtual ~NewCharacter() = default;

  void SetDoor(const std::vector<std::shared_ptr<NewDoor>> &door);
  void SetPool(const std::vector<std::shared_ptr<NewPool>> &pool);
  void SetBridge(const std::vector<std::shared_ptr<NewBridge>> &bridge);
  void
  SetElevators(const std::vector<std::shared_ptr<NewElevator>> &elevatorsList);
  void SetRock(const std::shared_ptr<NewRock> &rock) { rocks = rock; };

  void OnCollideY() {
    velocity.y = 0;
    isJumping = false;
  }
  virtual void MoveX(float amount,
                     const std::vector<MapBackground::Platform> &platforms,
                     std::string tag);
  virtual void MoveY(float amount,
                     const std::vector<MapBackground::Platform> &platforms);

  virtual void Update(float deltaTime,
                      const std::vector<MapBackground::Platform> &platforms){};

  bool IsCollidingWith(const MGameObject &other);
  bool IsOnGround(const std::vector<MapBackground::Platform> &platforms);
  void Jump();
  bool IsCollidingWithPlatform(const MapBackground::Platform &platform);

  std::string GetStatus();

protected:
  std::shared_ptr<NewRock> rocks;
  std::vector<std::shared_ptr<NewDoor>> doors;
  std::vector<std::shared_ptr<NewPool>> pools;
  std::vector<std::shared_ptr<NewBridge>> bridges;
  std::vector<std::shared_ptr<NewElevator>> elevators;

  std::string status = "Alive";
  bool isJumping = false;
  float collisionTimer = 0.0f;
  float jumpingBuffer = 0.0f;
  const float gravity = -300.0f;
  const float jumpSpeed = 200.0f;
  const float targethigh = 9;

  bool isOnElevator = true;
  bool isColliding = false;
  bool onRock = false;

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
